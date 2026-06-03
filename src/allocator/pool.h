#ifndef __EDSA_ALLOCATOR_POOL_H_
#define __EDSA_ALLOCATOR_POOL_H_

#include <stddef.h> /* size_t */

/**
 * @brief A node in the free list.
 *
 * @param next The next node in the free list.
 */
typedef struct AllocatorPoolFreeNode {
  struct AllocatorPoolFreeNode *next;
} AllocatorPoolFreeNode;

/**
 * @brief A fixed-size chunk allocator.
 *
 * @param buf        The backing buffer.
 * @param buf_len    The length of the backing buffer.
 * @param chunk_size The size of each chunk.
 * @param head       The head of the free list.
 */
typedef struct AllocatorPool {
  unsigned char *buf;
  size_t buf_len;
  size_t chunk_size;
  AllocatorPoolFreeNode *head;
} AllocatorPool;

/**
 * @brief Initializes the pool with a pre-allocated buffer.
 *
 * @param p                     The pool to initialize.
 * @param backing_buffer        The backing buffer.
 * @param backing_buffer_length The length of the backing buffer.
 * @param chunk_size            The size of each chunk.
 * @param chunk_alignment       The alignment of each chunk.
 */
void allocator_pool_init(
  AllocatorPool *p,
  void *backing_buffer,
  size_t backing_buffer_length,
  size_t chunk_size,
  size_t chunk_alignment
);

/**
 * @brief Allocates, reallocates, or frees a pool chunk.
 *
 * @param self The pool to allocate from.
 * @param ptr  The chunk to reallocate, or NULL to allocate a fresh chunk.
 * @param size The requested size, or 0 to free ptr.
 * @return The allocated chunk, or NULL when the request cannot be served.
 */
void *allocator_pool_alloc(void *self, void *ptr, size_t size);

/**
 * @brief Pushes a chunk onto the free list.
 *
 * @param self The pool.
 * @param ptr  The chunk to free.
 */
void allocator_pool_free(void *self, void *ptr);

/**
 * @brief Pushes every chunk onto the free list.
 *
 * @param p The pool.
 */
void allocator_pool_free_all(AllocatorPool *p);

#endif
