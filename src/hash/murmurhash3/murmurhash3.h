#ifndef __EDSA_MURMURHASH3_H_
#define __EDSA_MURMURHASH3_H_

#include "murmurhash3_implementation.h"

#include <stddef.h> /* size_t */

/**
 * @brief Wrapper for the murmurhash3 hash function
 * @param key
 * @param size
 * @return size_t hash
 */
#if (UINTPTR_MAX == UINT32_MAX)
static inline size_t murmurhash3_hash(const void *key, int size) {
  uint32_t hash[4];
  MurmurHash3_x86_128(key, size, 0, hash);
  return (size_t)hash[0];
}
#else
static inline size_t murmurhash3_hash(const void *key, int size) {
  uint64_t hash[2];
  MurmurHash3_x64_128(key, size, 0, hash);
  return (size_t)hash[0];
}
#endif

#endif
