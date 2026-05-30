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

#ifndef ALLOCATOR_ARENA_DEFAULT_ALIGNMENT
  #define ALLOCATOR_ARENA_DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

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
 * @brief resizes the arena to a new size (like a dynamic vector)
 *
 * @param a -> the arena pointer.
 * @param old_memory -> current memory from the arena
 * @param old_size -> current size
 * @param new_size
 * @return void* -> the newly allocated memory
 */
void *allocator_arena_resize(
  AllocatorArena *a, void *old_memory, size_t old_size, size_t new_size
);

/**
 * @brief Allocates a block of memory from the arena
 * @param a -> arena
 * @param size -> size of the block to allocate
 * @return void* -> pointer to the allocated block
 */
void *allocator_arena_alloc(AllocatorArena *a, size_t size);

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
