#ifndef __EDSA_FNV1A_H_
#define __EDSA_FNV1A_H_

#include "../../preprocessor/preprocessor.h"

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t, uint64_t */

/**
 * @brief Wrapper for the FNV-1a hash function
 * @param key
 * @param size
 * @return size_t hash
 */
#if PREPROCESSOR_32_BIT
static size_t hash_fnv1a(const void *key, size_t size) {
  const unsigned char *bp = (const unsigned char *)key;
  const unsigned char *be = bp + size;
  uint32_t hash           = (uint32_t)0x811c9dc5;

  while(bp < be) {
    hash ^= (uint32_t)*bp++;
    hash *= (uint32_t)0x01000193;
  }

  return (size_t)hash;
}
#else
static size_t hash_fnv1a(const void *key, size_t size) {
  const unsigned char *bp = (const unsigned char *)key;
  const unsigned char *be = bp + size;
  uint64_t hash           = (uint64_t)0xcbf29ce484222325ULL;

  while(bp < be) {
    hash ^= (uint64_t)*bp++;
    hash *= (uint64_t)0x100000001b3ULL;
  }

  return (size_t)hash;
}
#endif

#endif
