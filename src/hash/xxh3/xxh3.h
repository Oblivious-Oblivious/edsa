#ifndef __EDSA_HASH_XXH3_H_
#define __EDSA_HASH_XXH3_H_

#include "../../preprocessor/preprocessor.h"

/**
 * @brief Wrapper for the xxh3 hash function
 * @param key
 * @return size_t hash
 */
#define XXH_STATIC_LINKING_ONLY
#define XXH_INLINE_ALL
#if PREPROCESSOR_C_VERSION < 1999
  #define XXH_NO_LONG_LONG
#endif
#include "xxh3_implementation.h"

#if PREPROCESSOR_32_BIT || PREPROCESSOR_C_VERSION < 1999
  #define hash_xxh3(key, size) ((size_t)XXH32((key), (size), 0))
#else
  #define hash_xxh3(key, size) ((size_t)XXH3_64bits((key), (size)))
#endif

#endif
