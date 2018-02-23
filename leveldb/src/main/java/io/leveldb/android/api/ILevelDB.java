/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android.api;

import java.io.Closeable;
import java.io.IOException;

import io.leveldb.android.LevelDBExecption;

/**
 * Created by bunnyblue.
 */

public interface ILevelDB extends Closeable  {
    @DBApi
    public boolean openDB(String dbPath) throws LevelDBExecption;
    @DBApi
    public boolean repairDB(String dbPath) throws LevelDBExecption;
    @DBApi
    public boolean put(byte[] key, byte[] value0);
    @DBApi
    public boolean put(String key, String value0);




    @DBApi
    public byte[] get(byte[] key);
    @DBApi
    public String get(String key);


    @DBApi
    public byte[] get(ISnapshot snapshot, byte[] key);

    @DBApi
    public void delete(byte[] key);

    @DBApi
    public void write(ILevelDBWriter batch);

    @DBApi
    public ILevelIterator iterator();

    @DBApi
    public ILevelIterator iterator(final ISnapshot snapshot);

    @DBApi
    ISnapshot getSnapshot();

    @DBApi
    public void destroy();

    @DBApi
    @Override
    void close() throws IOException;


}
