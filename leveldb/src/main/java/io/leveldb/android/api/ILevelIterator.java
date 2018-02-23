/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android.api;

/**
 * Created by bunnyblue.
 */

public interface ILevelIterator {
    @DBApi
    void moveToFirst();

    @DBApi
    void moveToLast();

    @DBApi
    void seek(byte[] target);

    @DBApi
    boolean isValid();

    @DBApi
    void next();

    @DBApi
    void prev();

    @DBApi
    byte[] getKeyB();

    @DBApi
    byte[] getValueB();
    @DBApi
    String getKey();

    @DBApi
    String getValue();
    @DBApi
    void closeIterator();

}
