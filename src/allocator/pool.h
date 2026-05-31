#ifndef __EDSA_ALLOCATOR_POOL_H_
#define __EDSA_ALLOCATOR_POOL_H_

#include <stddef.h>

/**
 * @brief a node in the free list.
 * @param next the next node in the free list.
 */
typedef struct AllocatorPoolFreeNode {
  struct AllocatorPoolFreeNode *next;
} AllocatorPoolFreeNode;

/**
 * @brief defines a memory pool.
 * @param buf the buffer to store the memory pool.
 * @param buf_len the length of the buffer.
 * @param chunk_size the size of each chunk.
 * @param head the head of the free list.
 */
typedef struct AllocatorPool {
  unsigned char *buf;
  size_t buf_len;
  size_t chunk_size;
  AllocatorPoolFreeNode *head;
} AllocatorPool;

/**
 * @brief initialize the pool with a pre-allocated memory buffer
 * @param p the pool to initialize.
 * @param buf the buffer to initialize the pool with.
 * @param buf_len the length of the buffer.
 * @param chunk_size the size of each chunk.
 */
void allocator_pool_init(
  AllocatorPool *p,
  void *backing_buffer,
  size_t backing_buffer_length,
  size_t chunk_size,
  size_t chunk_alignment
);

/**
 * @brief pops off the head from the free list.
 * @param p the pool to pop off the head from.
 * @return the pointer to the allocated memory.
 */
void *allocator_pool_alloc(AllocatorPool *p);

/**
 * @brief pushes on the freed chunk as the head of the free list.
 * @param p the pool to push on the freed chunk to.
 * @param ptr the pointer to the freed chunk.
 */
void allocator_pool_free(AllocatorPool *p, void *ptr);

/**
 * @brief pushes every chunk in the pool onto the free list.
 * @param p the pool to push every chunk onto the free list.
 */
void allocator_pool_free_all(AllocatorPool *p);

#endif
