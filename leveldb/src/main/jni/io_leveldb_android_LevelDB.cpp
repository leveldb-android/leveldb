
#include "io_leveldb_android_LevelDB.h"
#include "util.h"
jmethodID gByteBuffer_isDirectMethodID;
jmethodID gByteBuffer_positionMethodID;
jmethodID gByteBuffer_limitMethodID;
jmethodID gByteBuffer_arrayMethodID;
using namespace leveldb;
JNIEXPORT jlong JNICALL Java_io_leveldb_android_LevelDB_nativeOpen(JNIEnv *env, jobject thisObj, jstring dbPath)
{
    const char *path = env->GetStringUTFChars(dbPath, 0);

    DB *db;
    Options options;
    options.create_if_missing = true;
    Status status = DB::Open(options, path, &db);
    env->ReleaseStringUTFChars(dbPath, path);

    if (!status.ok())
    {
        throwException(env, status);
    }

    return reinterpret_cast<jlong>(db);
}
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelDB_repair(JNIEnv *env, jobject thisObj, jstring dbPath)
{
    const char *path = env->GetStringUTFChars(dbPath, 0);

    DB *db;
    Options options;

    Status status = RepairDB(path, options);
    env->ReleaseStringUTFChars(dbPath, path);

    if (!status.ok())
    {
        throwException(env, status);
    }
}

JNIEXPORT void JNICALL Java_io_leveldb_android_LevelDB_close(JNIEnv *env, jobject dbObj, jlong ptr)
{
    DB *db = reinterpret_cast<DB *>(ptr);
    if (db)
    {
        delete db;
    }
}
/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    put
 * Signature: (J[B[B)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelDB_put(JNIEnv *env, jclass clazz, jlong dbPtr, jbyteArray keyObj, jbyteArray valObj)
{
    DB *db = reinterpret_cast<DB *>(dbPtr);

    size_t keyLen = env->GetArrayLength(keyObj);
    jbyte *keyBuf = env->GetByteArrayElements(keyObj, NULL);

    size_t valLen = env->GetArrayLength(valObj);
    jbyte *valBuf = env->GetByteArrayElements(valObj, NULL);

    Status status = db->Put(WriteOptions(),
                            Slice((const char *)keyBuf, keyLen),
                            Slice((const char *)valBuf, valLen));

    env->ReleaseByteArrayElements(keyObj, keyBuf, JNI_ABORT);
    env->ReleaseByteArrayElements(valObj, valBuf, JNI_ABORT);

    if (!status.ok())
    {
        throwException(env, status);
    }
}

/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    get
 * Signature: (JJ[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_io_leveldb_android_LevelDB_get__JJ_3B(JNIEnv *env, jclass, jlong dbPtr, jlong snapshotPtr, jbyteArray keyObj)
{
    DB *db = reinterpret_cast<DB *>(dbPtr);
    ReadOptions options = ReadOptions();
    options.snapshot = reinterpret_cast<Snapshot *>(snapshotPtr);

    size_t keyLen = env->GetArrayLength(keyObj);
    jbyte *buffer = env->GetByteArrayElements(keyObj, NULL);
    jbyteArray result;

    Slice key = Slice((const char *)buffer, keyLen);

    std::string val;
    Status status = db->Get(options, key, &val);
    if (status.ok())
    {
        Slice value = Slice(val);
        size_t len = value.size();

        result = env->NewByteArray(len);
        env->SetByteArrayRegion(result, 0, len, (const jbyte *)value.data());
    }
    else
    {
        result = NULL;
    }

    env->ReleaseByteArrayElements(keyObj, buffer, JNI_ABORT);

    return result;
}

/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    get
 * Signature: (JJLjava/nio/ByteBuffer;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_io_leveldb_android_LevelDB_get__JJLjava_nio_ByteBuffer_2(JNIEnv *env, jclass clazz, jlong dbPtr, jlong snapshotPtr, jobject keyObj)
{
    DB *db = reinterpret_cast<DB *>(dbPtr);
    ReadOptions options = ReadOptions();
    options.snapshot = reinterpret_cast<Snapshot *>(snapshotPtr);

    jint keyPos = env->CallIntMethod(keyObj, gByteBuffer_positionMethodID);
    jint keyLimit = env->CallIntMethod(keyObj, gByteBuffer_limitMethodID);
    jboolean keyIsDirect = env->CallBooleanMethod(keyObj, gByteBuffer_isDirectMethodID);
    jbyteArray keyArray;
    void *key;
    if (keyIsDirect)
    {
        key = env->GetDirectBufferAddress(keyObj);
        keyArray = NULL;
    }
    else
    {
        keyArray = (jbyteArray)env->CallObjectMethod(keyObj, gByteBuffer_arrayMethodID);
        key = (void *)env->GetByteArrayElements(keyArray, NULL);
    }

    jbyteArray result;

    Slice keySlice = Slice((const char *)key + keyPos, keyLimit - keyPos);
    std::string val;
    Status status = db->Get(options, keySlice, &val);
    if (status.ok())
    {
        Slice value = Slice(val);
        size_t len = value.size();
        result = env->NewByteArray(len);
        env->SetByteArrayRegion(result, 0, len, (const jbyte *)value.data());
    }
    else
    {
        result = NULL;
    }

    if (keyArray)
    {
        env->ReleaseByteArrayElements(keyArray, (jbyte *)key, JNI_ABORT);
    }

    return result;
}

/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    delete
 * Signature: (J[B)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelDB_delete(JNIEnv *env, jclass, jlong dbPtr, jbyteArray keyObj)
{
    DB *db = reinterpret_cast<DB *>(dbPtr);
    size_t keyLen = env->GetArrayLength(keyObj);
    jbyte *buffer = env->GetByteArrayElements(keyObj, NULL);

    Status status = db->Delete(WriteOptions(), Slice((const char *)buffer, keyLen));
    env->ReleaseByteArrayElements(keyObj, buffer, JNI_ABORT);

    if (!status.ok())
    {
        throwException(env, status);
    }
}

/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    write
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelDB_write(JNIEnv *env, jclass, jlong dbPtr, jlong batchPtr)
{
    DB *db = reinterpret_cast<DB *>(dbPtr);

    WriteBatch *batch = (WriteBatch *)batchPtr;
    Status status = db->Write(WriteOptions(), batch);
    if (!status.ok())
    {
        throwException(env, status);
    }
}

/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    destory
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelDB_destory(JNIEnv *env, jclass, jstring dbpath)
{
    const char *path = env->GetStringUTFChars(dbpath, 0);
    Options options;
    options.create_if_missing = true;
    Status status = DestroyDB(path, options);
    if (!status.ok())
    {
        throwException(env, status);
    }
}

/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    iterator
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_io_leveldb_android_LevelDB_iterator(JNIEnv *env, jclass, jlong dbPtr, jlong snapshotPtr)
{
    DB *db = reinterpret_cast<DB *>(dbPtr);
    ReadOptions options = ReadOptions();
    if (snapshotPtr != 0)
    {
        options.snapshot = reinterpret_cast<Snapshot *>(snapshotPtr);
    }

    Iterator *iter = db->NewIterator(options);
    return reinterpret_cast<jlong>(iter);
}

/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    getSnapshot
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_io_leveldb_android_LevelDB_getSnapshot(JNIEnv *env, jclass clazz, jlong dbPtr)
{
    DB *db = reinterpret_cast<DB *>(dbPtr);
    const Snapshot *snapshot = db->GetSnapshot();
    return reinterpret_cast<jlong>(snapshot);
}

/*
 * Class:     io_leveldb_android_LevelDB
 * Method:    releseSnapshot
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelDB_releseSnapshot(JNIEnv *env, jclass clazz, jlong dbPtr, jlong snapshotPtr)
{
    DB *db = reinterpret_cast<DB *>(dbPtr);
    const Snapshot *snapshot = reinterpret_cast<Snapshot *>(snapshotPtr);
    db->ReleaseSnapshot(snapshot);
}
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelDB_initLevelDB(JNIEnv *env, jclass clazz)
{
    jclass byteBuffer_Clazz = env->FindClass("java/nio/ByteBuffer");
    gByteBuffer_isDirectMethodID = env->GetMethodID(byteBuffer_Clazz,
                                                    "isDirect", "()Z");
    gByteBuffer_positionMethodID = env->GetMethodID(byteBuffer_Clazz,
                                                    "position", "()I");
    gByteBuffer_limitMethodID = env->GetMethodID(byteBuffer_Clazz,
                                                 "limit", "()I");
    gByteBuffer_arrayMethodID = env->GetMethodID(byteBuffer_Clazz,
                                                 "array", "()[B");
}
jint throwException(JNIEnv *env, Status status)
{
    const char *exceptionClass = "io/leveldb/android/LevelDBExecption";

    jclass clazz = env->FindClass(exceptionClass);
    if (!clazz)
    {
        LOGE("Can't find exception class %s", exceptionClass);
        return -1;
    }

    return env->ThrowNew(clazz, status.ToString().c_str());
}
