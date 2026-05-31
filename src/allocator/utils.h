#ifndef __EDSA_ALLOCATOR_UTILS_H_
#define __EDSA_ALLOCATOR_UTILS_H_

#include "../preprocessor/preprocessor.h"

#include <assert.h> /* assert */
#include <stddef.h> /* ptrdiff_t, size_t */
#include <stdint.h> /* uintptr_t */

/**
 * @brief can be overriden to change the default alignment for the allocator.
 */
#ifndef ALLOCATOR_DEFAULT_ALIGNMENT
  #define ALLOCATOR_DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

/**
 * @brief checks if a number is a power of two.
 * @param x the number to check.
 * @return true if the number is a power of two, false otherwise.
 */
p_inline bool allocator_is_power_of_two(ptrdiff_t x) {
  return (x & (x - 1)) == 0;
}

/**
 * @brief aligns a pointer forward to the next aligned address.
 * @param ptr the pointer to align.
 * @param align the alignment to align to.
 * @return the aligned pointer.
 */
p_inline ptrdiff_t allocator_align_forward(ptrdiff_t ptr, size_t align) {
  ptrdiff_t p, a, modulo;

  assert(allocator_is_power_of_two(align));

  p      = ptr;
  a      = (ptrdiff_t)align;
  modulo = p & (a - 1);

  if(modulo != 0) {
    /* If 'p' address is not aligned, push the address to the next value which
     * is aligned */
    p += a - modulo;
  }

  return p;
}

p_inline size_t allocator_align_forward_size(size_t ptr, size_t align) {
  size_t a, p, modulo;

  assert(allocator_is_power_of_two((ptrdiff_t)align));

  a      = align;
  p      = ptr;
  modulo = p & (a - 1);
  if(modulo != 0) {
    p += a - modulo;
  }
  return p;
}

#endif
