
#include "io_leveldb_android_WriteBatch.h"
#include "util.h"
/* Header for class io_leveldb_android_WriteBatch */

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    create
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_leveldb_android_WriteBatch_create(JNIEnv *, jobject)
{
    leveldb::WriteBatch *batch = new leveldb::WriteBatch();
    return reinterpret_cast<jlong>(batch);
}

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    destory
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_WriteBatch_destory(JNIEnv *, jclass, jlong ptr)
{
    leveldb::WriteBatch *batch = reinterpret_cast<leveldb::WriteBatch *>(ptr);
    delete batch;
}

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    delete
 * Signature: (JLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_WriteBatch_delete(JNIEnv *env, jclass, jlong ptr, jobject buffer)
{
    leveldb::WriteBatch *batch = reinterpret_cast<leveldb::WriteBatch *>(ptr);

    jint pos = env->CallIntMethod(buffer, gByteBuffer_positionMethodID);
    jint limit = env->CallIntMethod(buffer, gByteBuffer_limitMethodID);
    jboolean isDirect = env->CallBooleanMethod(buffer, gByteBuffer_isDirectMethodID);
    if (isDirect)
    {
        const char *bytes = (const char *)env->GetDirectBufferAddress(buffer);
        batch->Delete(leveldb::Slice(bytes + pos, limit - pos));
    }
    else
    {
        jbyteArray array = (jbyteArray)env->CallObjectMethod(buffer, gByteBuffer_arrayMethodID);
        jbyte *bytes = env->GetByteArrayElements(array, NULL);
        batch->Delete(leveldb::Slice((const char *)bytes + pos, limit - pos));
        env->ReleaseByteArrayElements(array, bytes, JNI_ABORT);
    }
}

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    put
 * Signature: (JLjava/nio/ByteBuffer;Ljava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_WriteBatch_put(JNIEnv *env, jclass, jlong ptr, jobject keyObj, jobject valObj)
{

    leveldb::WriteBatch *batch = reinterpret_cast<leveldb::WriteBatch *>(ptr);

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

    jint valPos = env->CallIntMethod(valObj, gByteBuffer_positionMethodID);
    jint valLimit = env->CallIntMethod(valObj, gByteBuffer_limitMethodID);
    jboolean valIsDirect = env->CallBooleanMethod(valObj, gByteBuffer_isDirectMethodID);
    jbyteArray valArray;
    void *val;
    if (valIsDirect)
    {
        val = env->GetDirectBufferAddress(valObj);
        valArray = NULL;
    }
    else
    {
        valArray = (jbyteArray)env->CallObjectMethod(valObj, gByteBuffer_arrayMethodID);
        val = (void *)env->GetByteArrayElements(valArray, NULL);
    }

    batch->Put(leveldb::Slice((const char *)key + keyPos, keyLimit - keyPos),
               leveldb::Slice((const char *)val + valPos, valLimit - valPos));

    if (keyArray)
    {
        env->ReleaseByteArrayElements(keyArray, (jbyte *)key, JNI_ABORT);
    }
    if (valArray)
    {
        env->ReleaseByteArrayElements(valArray, (jbyte *)val, JNI_ABORT);
    }
}

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    clear
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_WriteBatch_clear(JNIEnv *, jclass, jlong ptr)
{
    leveldb::WriteBatch *batch = reinterpret_cast<leveldb::WriteBatch *>(ptr);
    batch->Clear();
}
