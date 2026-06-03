#ifndef __EDSA_ALLOCATOR_ARENA_H_
#define __EDSA_ALLOCATOR_ARENA_H_

#include <stddef.h> /* size_t, ptrdiff_t */

typedef unsigned char AllocatorArenaBuf;

/**
 * @brief simple arena linear allocator
 * @param buf -> the buffer to allocate from
 * @param buf_len
 * @param prev_offset
 * @param curr_offset
 */
typedef struct AllocatorArena {
  AllocatorArenaBuf *buf;
  size_t buf_len;
  size_t prev_offset;
  size_t curr_offset;
} AllocatorArena;

/**
 * @brief Typical initialization, no malloc used.
 * @param a -> arena
 * @param backing_buffer -> buffer to allocate from
 * @param backing_buffer_len -> length of the buffer
 */
void allocator_arena_init(
  AllocatorArena *a, void *backing_buffer, size_t backing_buffer_len
);

/**
 * @brief Allocates, reallocates or frees memory from the arena, following the
 * realloc contract: a NULL ptr allocates a fresh block, a zero size frees ptr
 * and returns NULL, otherwise the block is resized preserving its contents.
 * @param a -> arena
 * @param ptr -> the block to resize, or NULL to allocate a fresh block
 * @param size -> the requested size (0 frees ptr)
 * @return void* -> pointer to the (re)allocated block, or NULL when size is 0
 */
void *allocator_arena_alloc(AllocatorArena *a, void *ptr, size_t size);

/**
 * @brief In an arena allocator this does nothing
 * @param a -> arena
 * @param ptr -> specific pointer to free
 */
void allocator_arena_free(AllocatorArena *a, void *ptr);

/**
 * @brief Frees the complete block by setting the pointer to zero.
 * @param a -> arena
 */
void allocator_arena_free_all(AllocatorArena *a);

#endif
