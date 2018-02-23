/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android.api;

import android.util.Log;

import java.io.Closeable;
import java.io.IOException;

import io.leveldb.android.LevelDBExecption;

/**
 * Created by bunnyblue.
 */
public abstract class LevelDBridge implements Closeable {
    protected long ptr = 0;
    protected volatile int ref = 0;

    protected LevelDBridge(long ptr) {
        this.ptr = ptr;
        if (ptr > 0)
            ref();

    }


    public long getPtr() {
        return ptr;
    }

    protected synchronized void ref() {
        ref++;
    }

    protected synchronized boolean isUsed() {
        return ref != 0;
    }

    protected synchronized void unref() {
        if (ref <= 0) {
            throw new IllegalStateException(String.format(" ptr %l ref count is already 0",ptr ));
        }

        ref--;

        if (ref == 0) {
            //   llAutoCloose(ptr);
            ptr = 0;
        }
    }

    // protected abstract void llAutoCloose(long ptr);

    @Override
    public void close() throws IOException {
        if (ref != 0) {
            unref();
        }

    }

    @Override
    protected void finalize() throws Throwable {
        if (ptr != 0) {
            throw new LevelDBExecption("ptr not release");
        }

        super.finalize();
    }

}