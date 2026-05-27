#ifndef __EDSA_HASH_KOMIHASH_H_
#define __EDSA_HASH_KOMIHASH_H_

#include "../../preprocessor/preprocessor.h"
#include "komihash_implementation.h"

/**
 * @brief Wrapper for the komihash hash function
 * @param key
 * @param size
 * @return size_t hash
 */
#if PREPROCESSOR_32_BIT
  #define hash_komihash(key, size) \
    ((size_t)(komihash((key), (size), 0x0123456789abcdef) & 0xFFFFFFFF))
#else
  #define hash_komihash(key, size) \
    ((size_t)komihash((key), (size), 0x0123456789abcdef))
#endif

#endif
