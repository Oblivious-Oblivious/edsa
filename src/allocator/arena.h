#ifndef __EDSA_ALLOCATOR_ARENA_H_
#define __EDSA_ALLOCATOR_ARENA_H_

#include <stddef.h> /* size_t, ptrdiff_t */

/**
 * @brief Simple arena linear allocator.
 *
 * @param buf         The buffer to allocate from.
 * @param buf_len     The length of the buffer.
 * @param prev_offset The previous allocation offset.
 * @param curr_offset The current allocation offset.
 */
typedef struct AllocatorArena {
  unsigned char *buf;
  size_t buf_len;
  size_t prev_offset;
  size_t curr_offset;
} AllocatorArena;

/**
 * @brief Initializes the arena with a pre-allocated buffer.
 *
 * @param a                  The arena to initialize.
 * @param backing_buffer     The buffer to allocate from.
 * @param backing_buffer_len The length of the buffer.
 */
void allocator_arena_init(
  AllocatorArena *a, void *backing_buffer, size_t backing_buffer_len
);

/**
 * @brief Allocates, reallocates, or frees memory from the arena.
 *
 * @param self The arena to allocate from.
 * @param ptr  The block to reallocate, or NULL to allocate a fresh block.
 * @param size The requested size, or 0 to free ptr.
 * @return The allocated block, or NULL when the request cannot be served.
 */
void *allocator_arena_alloc(void *self, void *ptr, size_t size);

/**
 * @brief Does nothing for arena allocations.
 *
 * @param self The arena.
 * @param ptr  The block to free.
 */
void allocator_arena_free(void *self, void *ptr);

/**
 * @brief Resets all arena offsets.
 *
 * @param a The arena to reset.
 */
void allocator_arena_free_all(AllocatorArena *a);

#endif
