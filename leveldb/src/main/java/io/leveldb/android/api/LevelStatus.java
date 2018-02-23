/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android.api;

/**
 * leveldb::Status
 * Created by bunnyblue on 2/9/18.
 */

public enum LevelStatus {

    kOk,
    kNotFound,
    kCorruption,
    kNotSupported,
    kInvalidArgument,
    kIOError

}
