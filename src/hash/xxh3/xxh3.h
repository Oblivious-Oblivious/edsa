#ifndef __EDSA_XXH3_H_
#define __EDSA_XXH3_H_

/**
 * @brief Wrapper for the xxh3 hash function
 * @param key
 * @return size_t hash
 */
#define XXH_STATIC_LINKING_ONLY
#define XXH_IMPLEMENTATION
#include "xxh3_implementation.h"

#if (UINTPTR_MAX == UINT32_MAX)
  #define xxh3_hash(key, size) ((size_t)XXH32((key), (size), 0))
#else
  #define xxh3_hash(key, size) ((size_t)XXH3_64bits((key), (size)))
#endif

#endif
