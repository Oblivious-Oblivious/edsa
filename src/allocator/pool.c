#include "pool.h"

#include "utils.h"

#include <assert.h> /* assert */
#include <stdint.h> /* uintptr_t */
#include <string.h> /* memset */

void allocator_pool_init(
  AllocatorPool *p,
  void *backing_buffer,
  size_t backing_buffer_length,
  size_t chunk_size,
  size_t chunk_alignment
) {
  // Align backing buffer to the specified chunk alignment
  uintptr_t initial_start = (uintptr_t)backing_buffer;
  uintptr_t start =
    allocator_align_forward(initial_start, (uintptr_t)chunk_alignment);
  backing_buffer_length -= (size_t)(start - initial_start);

  // Align chunk size up to the required chunk_alignment
  chunk_size = allocator_align_forward_size(chunk_size, chunk_alignment);

  // Assert that the parameters passed are valid
  assert(
    chunk_size >= sizeof(AllocatorPoolFreeNode) && "Chunk size is too small"
  );
  assert(
    backing_buffer_length >= chunk_size &&
    "Backing buffer length is smaller than the chunk size"
  );

  // Store the adjusted parameters
  p->buf        = (unsigned char *)backing_buffer;
  p->buf_len    = backing_buffer_length;
  p->chunk_size = chunk_size;
  p->head       = NULL; // Free List Head

  // Set up the free list for free chunks
  allocator_pool_free_all(p);
}

void *allocator_pool_alloc(AllocatorPool *p) {
  // Get latest free node
  AllocatorPoolFreeNode *node = p->head;

  if(node == NULL) {
    assert(0 && "Pool allocator has no free memory");
    return NULL;
  }

  // Pop free node
  p->head = p->head->next;

  // Zero memory by default
  return memset(node, 0, p->chunk_size);
}

void allocator_pool_free(AllocatorPool *p, void *ptr) {
  AllocatorPoolFreeNode *node = NULL;

  void *start = p->buf;
  void *end   = &p->buf[p->buf_len];

  if(ptr == NULL) {
    // Ignore NULL pointers
    return;
  }

  if(!(start <= ptr && ptr < end)) {
    assert(0 && "Memory is out of bounds of the buffer in this pool");
    return;
  }

  // Push free node
  node       = (AllocatorPoolFreeNode *)ptr;
  node->next = p->head;
  p->head    = node;
}

void allocator_pool_free_all(AllocatorPool *p) {
  size_t chunk_count = p->buf_len / p->chunk_size;
  size_t i;

  // Set all chunks to be free
  for(i = 0; i < chunk_count; i++) {
    void *ptr                   = &p->buf[i * p->chunk_size];
    AllocatorPoolFreeNode *node = (AllocatorPoolFreeNode *)ptr;
    // Push free node onto thte free list
    node->next                  = p->head;
    p->head                     = node;
  }
}
