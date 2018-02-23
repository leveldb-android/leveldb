/*
 * Copyright (c) LevelDB-Android Project 2018.
 * https://github.com/leveldb-android/leveldb.git
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

package io.leveldb.android.leveldb;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import java.io.File;
import java.io.IOException;

import io.leveldb.android.LevelDB;
import io.leveldb.android.LevelDBExecption;
import io.leveldb.android.WriteBatch;
import io.leveldb.android.api.ILevelDB;
import io.leveldb.android.api.ILevelIterator;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ILevelDB levelDB=new LevelDB();
        try {
            boolean dbPtr = levelDB.openDB(new File(getFilesDir(), "test.ldb").getAbsolutePath());
           if (true){
               levelDB.put("tes21".getBytes(),"password".getBytes());
                levelDB.put("test1".getBytes(),"password".getBytes());
                levelDB.put("test22".getBytes(),"password".getBytes());
                WriteBatch writeBatch=new WriteBatch();
                writeBatch.put("hello23".getBytes(),"hello2".getBytes());
                System.err.println();
                levelDB.write(writeBatch);
            }
            ILevelIterator iLevelIterator2=levelDB.iterator();

            ILevelIterator iLevelIterator=levelDB.iterator();
            iLevelIterator.moveToFirst();

            while (iLevelIterator.isValid()){

                Log.e("tmp", "onCreate:  "+ new String(iLevelIterator.getKey())+" "+ new String(iLevelIterator.getValue()));
                iLevelIterator.next();
            }
            iLevelIterator.closeIterator();
            iLevelIterator2.closeIterator();
            Log.d("test",new String(levelDB.get("test1".getBytes())));
            levelDB.close();
        } catch (LevelDBExecption levelDBExecption) {
            levelDBExecption.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
