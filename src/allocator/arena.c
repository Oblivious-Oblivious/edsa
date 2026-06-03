#include "arena.h"

#include "utils.h"

#include <string.h> /* memset */

void allocator_arena_init(
  AllocatorArena *a, void *backing_buffer, size_t backing_buffer_len
) {
  a->buf         = backing_buffer;
  a->buf_len     = backing_buffer_len;
  a->curr_offset = 0;
  a->prev_offset = 0;
}

void *allocator_arena_alloc(void *self, void *ptr, size_t size) {
  AllocatorArena *a = self;
  unsigned char *old_mem;
  uintptr_t curr_ptr;
  size_t offset;

  if(size == 0) {
    allocator_arena_free(a, ptr);
    return NULL;
  }

  if(ptr == NULL) {
    curr_ptr = (uintptr_t)a->buf + a->curr_offset;
    offset   = allocator_align_forward(curr_ptr, ALLOCATOR_DEFAULT_ALIGNMENT) -
               (uintptr_t)a->buf;

    if(offset + size > a->buf_len) {
      return NULL;
    }

    a->prev_offset = offset;
    a->curr_offset = offset + size;

    return memset(a->buf + offset, 0, size);
  }

  old_mem = ptr;
  if(old_mem < a->buf || old_mem >= a->buf + a->buf_len) {
    return NULL;
  }

  if(a->buf + a->prev_offset == old_mem) {
    size_t old_size = a->curr_offset - a->prev_offset;
    a->curr_offset  = a->prev_offset + size;

    if(size > old_size) {
      memset(a->buf + a->prev_offset + old_size, 0, size - old_size);
    }

    return old_mem;
  }

  size_t available = (size_t)(a->buf + a->buf_len - old_mem);
  size_t copy_size = size < available ? size : available;
  void *new_mem    = allocator_arena_alloc(a, NULL, size);

  if(new_mem != NULL) {
    memmove(new_mem, old_mem, copy_size);
  }

  return new_mem;
}

void allocator_arena_free(void *self, void *ptr) {
  (void)self;
  (void)ptr;
}

void allocator_arena_free_all(AllocatorArena *a) {
  a->curr_offset = 0;
  a->prev_offset = 0;
}
