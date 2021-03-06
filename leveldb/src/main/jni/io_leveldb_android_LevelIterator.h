/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class io_leveldb_android_LevelIterator */

#ifndef _Included_io_leveldb_android_LevelIterator
#define _Included_io_leveldb_android_LevelIterator
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    destory
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelIterator_destory
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    seekToFirst
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelIterator_seekToFirst
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    seekToLast
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelIterator_seekToLast
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    seek
 * Signature: (J[B)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelIterator_seek
  (JNIEnv *, jclass, jlong, jbyteArray);

/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    valid
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_io_leveldb_android_LevelIterator_valid
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    next
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelIterator_next
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    prev
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_io_leveldb_android_LevelIterator_prev
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    key
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_io_leveldb_android_LevelIterator_key
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_leveldb_android_LevelIterator
 * Method:    value
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_io_leveldb_android_LevelIterator_value
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
