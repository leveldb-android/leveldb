/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android;


import io.leveldb.android.api.ILevelIterator;
import io.leveldb.android.api.LevelDBridge;

/**
 * Created by bunnyblue.
 */
@SuppressWarnings("JniMissingFunction")
public class LevelIterator extends LevelDBridge implements ILevelIterator {

    /**
     * snapshot native point
     *
     * @param ptr
     */
    protected LevelIterator(long ptr) {
        super(ptr);
    }

    private static native void destory(long ptr);

    private static native void seekToFirst(long ptr);

    private static native void seekToLast(long ptr);

    private static native void seek(long ptr, byte[] key);

    private static native boolean valid(long ptr);

    private static native void next(long ptr);

    private static native void prev(long ptr);

    private static native byte[] key(long ptr);

    private static native byte[] value(long ptr);

    @Override
    public void moveToFirst() {

        seekToFirst(getPtr());
    }

    @Override
    public void moveToLast() {

        seekToLast(getPtr());
    }

    @Override
    public void seek(byte[] target) {

        if (target == null) {
            throw new IllegalArgumentException();
        }
        seek(getPtr(), target);
    }

    @Override
    public boolean isValid() {

        return valid(getPtr());
    }

    @Override
    public void next() {

        next(getPtr());
    }

    @Override
    public void prev() {

        prev(getPtr());
    }

    @Override
    public byte[] getKeyB() {

        return key(getPtr());
    }

    @Override
    public byte[] getValueB() {

        return value(getPtr());
    }

    @Override
    public String getKey() {
        return new String(key(getPtr()));
    }

    @Override
    public String getValue() {
        return new String(value(getPtr()));
    }

    @Override
    public void closeIterator() {
        unref();
        destory(ptr);

    }

}
