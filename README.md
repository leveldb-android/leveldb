#LevelDB on Android

`compile 'io.leveldb.android:leveldb:1.2.0.1'`

## sample
```
boolean dbPtr = levelDB.openDB(new File(getFilesDir(), "test.ldb").getAbsolutePath());
if (true){
   levelDB.put("tes21".getBytes(),"password".getBytes());
    levelDB.put("test1".getBytes(),"password".getBytes());
    levelDB.put("test22".getBytes(),"password".getBytes());
    WriteBatch writeBatch=new WriteBatch();
    writeBatch.put("hello23".getBytes(),"hello2".getBytes());
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

```



# leveldb native
version 1.2.0

# snappy
version 1.1.7
