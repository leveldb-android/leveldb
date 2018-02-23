/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android;

import android.support.annotation.NonNull;

import java.io.IOException;
import java.nio.ByteBuffer;

import io.leveldb.android.api.DBApi;
import io.leveldb.android.api.ILevelDBWriter;
import io.leveldb.android.api.LevelDBridge;

/**
 * Created by bunnyblue.
 */
@SuppressWarnings("JniMissingFunction")
public class WriteBatch extends LevelDBridge implements ILevelDBWriter {

    public WriteBatch() {
        super(create());
    }

    private static native long create();

    private static native void destory(long ptr);

    private static native void delete(long ptr, ByteBuffer key);

    private static native void put(long ptr, ByteBuffer key, ByteBuffer val);

    private static native void clear(long ptr);

    @DBApi
    @Override
    public void delete(ByteBuffer key) {

        if (key == null) {
            throw new NullPointerException("key");
        }

        delete(ptr, key);
    }

    @Override
    public void delete(@NonNull String key) {
        delete(ptr, ByteBuffer.wrap(key.getBytes()));
    }

    @DBApi
    @Override
    public void put(ByteBuffer key, ByteBuffer value) {

        if (key == null) {
            throw new NullPointerException("key");
        }
        if (value == null) {
            throw new NullPointerException("value");
        }

        put(ptr, key, value);
    }

    @DBApi
    @Override
    public void put(byte[] key, byte[] value) {
        if (key == null) {
            throw new NullPointerException("key");
        }
        if (value == null) {
            throw new NullPointerException("value");
        }
        put(ptr, ByteBuffer.wrap(key), ByteBuffer.wrap(value));

    }

    @Override
    public void put(@NonNull String key, @NonNull String value) {
        put(ptr, ByteBuffer.wrap(key.getBytes()), ByteBuffer.wrap(value.getBytes()));

    }

    @DBApi
    @Override
    public void clear() {
        clear(ptr);
    }


    @Override
    public void close() throws IOException {
        super.close();

        destory(ptr);
        ptr = 0;
    }
}
