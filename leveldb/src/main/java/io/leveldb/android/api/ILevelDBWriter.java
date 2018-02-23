/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android.api;

import android.support.annotation.NonNull;

import java.io.Closeable;
import java.io.IOException;
import java.nio.ByteBuffer;

/**
 * Created by bunnyblue.
 */

public interface ILevelDBWriter extends Closeable {
    @DBApi
    void delete(@NonNull ByteBuffer key);
    @DBApi
    void delete(@NonNull String key);

    @DBApi
    void put(@NonNull ByteBuffer key, @NonNull ByteBuffer value);

    @DBApi
    void put(@NonNull byte[] key, @NonNull byte[] value);
    @DBApi
    void put(@NonNull String key,@NonNull String value);

    @DBApi
    void clear();

    long getPtr();

    @DBApi
    @Override
    void close() throws IOException;
}
