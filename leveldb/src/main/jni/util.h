#ifndef LEVELDB_UTIL_H_
#define LEVELDB_UTIL_H_

#include <jni.h>
#include <android/log.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

#define NELEM(x) ((int)(sizeof(x) / sizeof((x)[0])))
#define LOG_TAG "LevelDB"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
extern jmethodID gByteBuffer_isDirectMethodID;
extern jmethodID gByteBuffer_positionMethodID;
extern jmethodID gByteBuffer_limitMethodID;
extern jmethodID gByteBuffer_arrayMethodID;
jint throwException(JNIEnv *env, leveldb::Status status);

#endif /* LEVELDB_UTIL_H_ */
