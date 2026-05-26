#ifndef __EDSA_KOMIHASH_H_
#define __EDSA_KOMIHASH_H_

#include "komihash_implementation.h"

/**
 * @brief Wrapper for the komihash hash function
 * @param key
 * @param size
 * @return size_t hash
 */
#if (UINTPTR_MAX == UINT32_MAX)
  #define komihash_hash(key, size) \
    ((size_t)(komihash((key), (size), 0x0123456789abcdef) & 0xFFFFFFFF))
#else
  #define komihash_hash(key, size) \
    ((size_t)komihash((key), (size), 0x0123456789abcdef))
#endif

#endif
