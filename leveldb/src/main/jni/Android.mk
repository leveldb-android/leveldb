# Copyright (c) 2011 The LevelDB Authors. All rights reserved.                 # Use of this source code is governed by a BSD-style license that can be       # found in the LICENSE file. See the AUTHORS file for names of contributors.

# To build for Android, add the Android NDK to your path and type 'ndk-build'.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


include $(LOCAL_PATH)/leveldb/common.mk

LOCAL_MODULE := leveldb
LOCAL_C_INCLUDES := $(C_INCLUDES)  $(LOCAL_PATH)/snappy
LOCAL_CPP_EXTENSION := .cc .cpp
LOCAL_CFLAGS := -DLEVELDB_PLATFORM_ANDROID -std=gnu++0x -D_REENTRANT -DOS_ANDROID   -DSNAPPY -DNDEBUG
LOCAL_SRC_FILES := $(SOURCES:%.cc=leveldb/%.cc) \
   port/port_android.cc io_leveldb_android_LevelDB.cpp \
   io_leveldb_android_LevelIterator.cpp \
   io_leveldb_android_WriteBatch.cpp
LOCAL_STATIC_LIBRARIES += snappy
LOCAL_LDLIBS +=  -llog

include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE := snappy
LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES := snappy/snappy.cc snappy/snappy-sinksource.cc

include $(BUILD_STATIC_LIBRARY)
