#ifndef __EDSA_ALLOCATOR_UTILS_H_
#define __EDSA_ALLOCATOR_UTILS_H_

#include "../preprocessor/preprocessor.h"

#include <stddef.h> /* ptrdiff_t, size_t */
#include <stdint.h> /* uintptr_t */

/**
 * @brief The default alignment for allocator allocations.
 */
#ifndef ALLOCATOR_DEFAULT_ALIGNMENT
  #define ALLOCATOR_DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

/**
 * @brief Checks whether a number is a power of two.
 *
 * @param x The number to check.
 * @return true when x is a power of two, false otherwise.
 */
p_inline bool allocator_is_power_of_two(size_t x) { return (x & (x - 1)) == 0; }

/**
 * @brief Aligns a pointer-sized value forward.
 *
 * @param ptr   The value to align.
 * @param align The alignment to use.
 * @return The aligned value.
 */
p_inline uintptr_t allocator_align_forward(uintptr_t ptr, size_t align) {
  size_t modulo;

  if(!allocator_is_power_of_two(align)) {
    return ptr;
  }

  modulo = ptr & (align - 1);
  return modulo == 0 ? ptr : ptr + align - modulo;
}

/**
 * @brief Aligns a size forward.
 *
 * @param size  The size to align.
 * @param align The alignment to use.
 * @return The aligned size.
 */
p_inline size_t allocator_align_forward_size(size_t size, size_t align) {
  return allocator_align_forward(size, align);
}

#endif
