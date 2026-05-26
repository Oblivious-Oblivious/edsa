#ifndef __EDSA_FNV1A_H_
#define __EDSA_FNV1A_H_

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t, uint64_t */

/**
 * @brief Wrapper for the FNV-1a hash function
 * @param key
 * @param size
 * @return size_t hash
 */
#if (UINTPTR_MAX == UINT32_MAX)
static size_t fnv1a_hash(const void *key, size_t size) {
  const unsigned char *bp = (const unsigned char *)key;
  const unsigned char *be = bp + size;
  uint32_t hash           = UINT32_C(0x811c9dc5);

  while(bp < be) {
    hash ^= (uint32_t)*bp++;
    hash *= UINT32_C(0x01000193);
  }

  return (size_t)hash;
}
#else
static size_t fnv1a_hash(const void *key, size_t size) {
  const unsigned char *bp = (const unsigned char *)key;
  const unsigned char *be = bp + size;
  uint64_t hash           = UINT64_C(0xcbf29ce484222325);

  while(bp < be) {
    hash ^= (uint64_t)*bp++;
    hash *= UINT64_C(0x100000001b3);
  }

  return (size_t)hash;
}
#endif

#endif
