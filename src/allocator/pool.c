#include "pool.h"

#include "utils.h"

#include <stdint.h> /* uintptr_t */
#include <string.h> /* memset */

void allocator_pool_init(
  AllocatorPool *p,
  void *backing_buffer,
  size_t backing_buffer_length,
  size_t chunk_size,
  size_t chunk_alignment
) {
  uintptr_t start         = (uintptr_t)backing_buffer;
  uintptr_t aligned_start = allocator_align_forward(start, chunk_alignment);

  backing_buffer_length -= aligned_start - start;
  chunk_size = allocator_align_forward(chunk_size, chunk_alignment);

  if(
    chunk_size < sizeof(AllocatorPoolFreeNode) ||
    backing_buffer_length < chunk_size
  ) {
    return;
  }

  p->buf        = backing_buffer;
  p->buf_len    = backing_buffer_length;
  p->chunk_size = chunk_size;
  p->head       = NULL;

  allocator_pool_free_all(p);
}

void *allocator_pool_alloc(void *self, void *ptr, size_t size) {
  AllocatorPool *p = (AllocatorPool *)self;
  AllocatorPoolFreeNode *node;

  if(size == 0) {
    allocator_pool_free(p, ptr);
    return NULL;
  }

  if(ptr != NULL) {
    return size <= p->chunk_size ? ptr : NULL;
  }

  if(size > p->chunk_size || p->head == NULL) {
    return NULL;
  }

  node    = p->head;
  p->head = node->next;

  return memset(node, 0, p->chunk_size);
}

void allocator_pool_free(void *self, void *ptr) {
  AllocatorPool *p            = (AllocatorPool *)self;
  AllocatorPoolFreeNode *node = NULL;

  if(
    ptr == NULL || ptr < (void *)p->buf || ptr >= (void *)(p->buf + p->buf_len)
  ) {
    return;
  }

  node       = (AllocatorPoolFreeNode *)ptr;
  node->next = p->head;
  p->head    = node;
}

void allocator_pool_free_all(AllocatorPool *p) {
  size_t i;
  size_t chunk_count = p->buf_len / p->chunk_size;

  p->head = NULL;

  for(i = 0; i < chunk_count; i++) {
    uintptr_t chunk             = (uintptr_t)p->buf + i * p->chunk_size;
    AllocatorPoolFreeNode *node = (void *)chunk;
    node->next                  = p->head;
    p->head                     = node;
  }
}
