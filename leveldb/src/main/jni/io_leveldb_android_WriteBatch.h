/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class io_leveldb_android_WriteBatch */

#ifndef _Included_io_leveldb_android_WriteBatch
#define _Included_io_leveldb_android_WriteBatch
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    create
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_leveldb_android_WriteBatch_create
  (JNIEnv *, jobject);

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    destory
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_WriteBatch_destory
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    delete
 * Signature: (JLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_WriteBatch_delete
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    put
 * Signature: (JLjava/nio/ByteBuffer;Ljava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_WriteBatch_put
  (JNIEnv *, jclass, jlong, jobject, jobject);

/*
 * Class:     io_leveldb_android_WriteBatch
 * Method:    clear
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_WriteBatch_clear
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
