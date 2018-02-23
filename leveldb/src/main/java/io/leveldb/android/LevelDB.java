/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android;

import java.io.IOException;
import java.nio.ByteBuffer;

import io.leveldb.android.api.DBApi;
import io.leveldb.android.api.ILevelDB;
import io.leveldb.android.api.ILevelDBWriter;
import io.leveldb.android.api.ILevelIterator;
import io.leveldb.android.api.ISnapshot;
import io.leveldb.android.api.LevelDBridge;

/**
 * Created by bunnyblue.
 */
@SuppressWarnings("JniMissingFunction")
public class LevelDB extends LevelDBridge implements ILevelDB {
    private static boolean load = false;

    static {
        try {
            System.loadLibrary("leveldb");
            initLevelDB();
            load = true;
        } catch (Exception exception) {
            exception.printStackTrace();
        }

    }

    private String dbPath = null;

    public LevelDB() {
        super(0);
    }

    private static native void initLevelDB();

    private static native void put(long ptr, byte[] key, byte[] value);

    private static native byte[] get(long ptr, long snapshotPtr, byte[] key);

    private static native byte[] get(long ptr, long snapshotPtr, ByteBuffer key);

    private static native void delete(long ptr, byte[] key);

    private static native void write(long ptr, long batchPtr) throws LevelDBExecption;

    private static native void destory(String dbpath);

    private static native long iterator(long ptr, long snapshotPtr);

    private static native long getSnapshot(long ptr);

    private static native void releseSnapshot(long ptr, long snapshotPtr);

    @Override
    @DBApi
    public boolean openDB(String dbPath) throws LevelDBExecption {
        if (!load) {
            throw new LevelDBExecption("leveldb can't load");
        }
        if (getPtr() == 0) {
            ptr = nativeOpen(dbPath);
            if (getPtr() != 0) {
                ref();
                return true;
            }
        } else {
            throw new LevelDBExecption("db has opened!!");
        }
        return false;

    }

    @Override
    public boolean repairDB(String dbPath) throws LevelDBExecption {
        return false;
    }

    @Override
    @DBApi
    public boolean put(byte[] key, byte[] value0) {
        put(ptr, key, value0);
        return true;
    }

    @Override
    public boolean put(String key, String value0) {
        put(ptr, key.getBytes(), value0.getBytes());
        return true;
    }

    @Override
    @DBApi
    public byte[] get(byte[] key) {
        return get(null, key);
    }

    @Override
    public String get(String key) {
        byte[] val = get(null, key.getBytes());
        if(val==null){
            return null;
        }
        return new String(val);
    }

    @Override
    @DBApi
    public byte[] get(ISnapshot snapshot, byte[] key) {
        if (key == null) {
            throw new NullPointerException();
        }

        return get(getPtr(), snapshot != null ? snapshot.getPtr() : 0, key);
    }

    @Override
    @DBApi
    public void delete(byte[] key) {

        if (key == null) {
            throw new NullPointerException();
        }
        delete(ptr, key);
    }

    @Override
    @DBApi
    public void write(ILevelDBWriter batch) {

        if (batch == null) {
            throw new NullPointerException();
        }


        try {
            write(getPtr(), batch.getPtr());
            batch.clear();
            batch.close();
        } catch (IOException e) {

        } catch (LevelDBExecption execption) {

        }
    }

    @DBApi
    public ILevelIterator iterator() {
        return iterator(null);
    }

    @DBApi
    public ILevelIterator iterator(final ISnapshot snapshot) {


        ref();


        if (snapshot != null) {
            ((Snapshot) snapshot).ref();
        }

        return new LevelIterator(iterator(ptr, snapshot != null ? snapshot.getPtr() : 0)) {
            @Override
            public void closeIterator() {
                super.closeIterator();
                if (snapshot != null) {
                    ((Snapshot) snapshot).unref();
                }
                LevelDB.this.unref();
            }


        };
    }

    @DBApi
    public ISnapshot getSnapshot() {

        ref();
        return new Snapshot(ptr, getSnapshot(ptr)) {
//            @Override
//            protected void llAutoCloose(long ptr) {
//                releseSnapshot(LevelDB.this.ptr, getPtr());
//                LevelDB.this.unref();
//            }
        };
    }

    @DBApi
    public void destroy() {
        //   mDestroyOnClose = true;
        if (getPtr() == 0) {
            destory(dbPath);
        }
    }

    private native long nativeOpen(String dbPath);

    private native long repairD(String dbPath);

    private native void close(long ptr);

//    @Override
//    protected final void llAutoCloose(long ptr) {
//
//    }

    private static class Snapshot extends LevelDBridge implements ISnapshot {
        private long dbPtr;

        protected Snapshot(long dbPtr, long ptr) {
            super(ptr);
            this.dbPtr = dbPtr;
        }

//        @Override
//        protected void llAutoCloose(long ptr) {
//            releseSnapshot(dbPtr, ptr);
//
//        }

        @Override
        protected synchronized void unref() {
            super.unref();
        }

        @Override
        protected synchronized void ref() {
            super.ref();
        }
    }

    @Override
    public void close() throws IOException {
        super.close();
        if (isUsed()) {
            ref();
            throw new IOException(String.format("can't close db  %d", ref));
        } else {
            close(ptr);
        }
    }


}
