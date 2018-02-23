// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// See port_example.h for documentation for the following types/functions.

#ifndef STORAGE_LEVELDB_PORT_PORT_ANDROID_H_
#define STORAGE_LEVELDB_PORT_PORT_ANDROID_H_

#include <endian.h>
#include <pthread.h>
#include <stdint.h>
#include <atomic>
#include <string>
#include <cctype>
#include <unistd.h>
#include <string.h>

// Collapse the plethora of ARM flavors available to an easier to manage set
// Defs reference is at https://wiki.edubuntu.org/ARM/Thumb2PortingHowto
#if defined(__ARM_ARCH_6__) || \
    defined(__ARM_ARCH_6J__) || \
    defined(__ARM_ARCH_6K__) || \
    defined(__ARM_ARCH_6Z__) || \
    defined(__ARM_ARCH_6T2__) || \
    defined(__ARM_ARCH_6ZK__) || \
    defined(__ARM_ARCH_7__) || \
    defined(__ARM_ARCH_7R__) || \
    defined(__ARM_ARCH_7A__)
#define ARMV6_OR_7 1
#endif

#if defined(_M_X64) || defined(__x86_64__)
#define ARCH_CPU_X86_FAMILY 1
#elif defined(_M_IX86) || defined(__i386__) || defined(__i386)
#define ARCH_CPU_X86_FAMILY 1
#elif defined(__ARMEL__)
#define ARCH_CPU_ARM_FAMILY 1
#elif defined(__aarch64__)
#define ARCH_CPU_ARM64_FAMILY 1
#elif defined(__ppc__) || defined(__powerpc__) || defined(__powerpc64__)
#define ARCH_CPU_PPC_FAMILY 1
#elif defined(__mips__)
#define ARCH_CPU_MIPS_FAMILY 1
#endif

extern "C" {
  size_t fread_unlocked(void *a, size_t b, size_t c, FILE *d);
  size_t fwrite_unlocked(const void *a, size_t b, size_t c, FILE *d);
  int fflush_unlocked(FILE *f);
  int fdatasync (int fd);
}

namespace leveldb {
namespace port {

static const bool kLittleEndian = __BYTE_ORDER == __LITTLE_ENDIAN;

class CondVar;

class Mutex {
 public:
  Mutex();
  ~Mutex();

  void Lock();
  void Unlock();
  void AssertHeld() {
    //TODO(gabor): How can I implement this?
  }

 private:
  friend class CondVar;
  pthread_mutex_t mu_;

  // No copying
  Mutex(const Mutex&);
  void operator=(const Mutex&);
};

class CondVar {
 public:
  explicit CondVar(Mutex* mu);
  ~CondVar();
  void Wait();
  void Signal();
  void SignalAll();
 private:
  Mutex* mu_;
  pthread_cond_t cv_;
};


// Storage for a lock-free pointer
class AtomicPointer {
 private:
  void* rep_;

  inline void MemoryBarrier() const {
    // TODO(gabor): This only works on Android instruction sets >= V6
#if  defined(__aarch64__)
  asm volatile("dmb sy" : : : "memory");
#endif
#if defined(ARMV6_OR_7)
    __asm__ __volatile__("dmb" : : : "memory");
#endif

  }

 public:
  AtomicPointer() { }
  explicit AtomicPointer(void* v) : rep_(v) { }
  inline void* Acquire_Load() const {
    void* r = rep_;
    MemoryBarrier();
    return r;
  }
  inline void Release_Store(void* v) {
    MemoryBarrier();
    rep_ = v;
  }
  inline void* NoBarrier_Load() const {
    void* r = rep_;
    return r;
  }
  inline void NoBarrier_Store(void* v) {
    rep_ = v;
  }
};

// TODO(gabor): Implement compress
inline bool Snappy_Compress(
    const char* input,
    size_t input_length,
    std::string* output) {
  return false;
}

// TODO(gabor): Implement uncompress
inline bool Snappy_GetUncompressedLength(const char* input, size_t length,
                                         size_t* result) {
  return false;
}

// TODO(gabor): Implement uncompress
inline bool Snappy_Uncompress(
    const char* input_data,
    size_t input_length,
    char* output) {
  return false;
}

inline uint64_t ThreadIdentifier() {
  pthread_t tid = pthread_self();
  uint64_t r = 0;

  memcpy(&r, &tid, sizeof(r) < sizeof(tid) ? sizeof(r) : sizeof(tid));

  return r;
}

inline bool GetHeapProfile(void (*func)(void*, const char*, int), void* arg) {
  return false;
}

}
}

#endif  // STORAGE_LEVELDB_PORT_PORT_ANDROID_H_
