#include "arena.h"

#include "../boolean/boolean.h"
#include "../preprocessor/preprocessor.h"
#include "utils.h"

#include <string.h> /* memset */

void allocator_arena_init(
  AllocatorArena *a, void *backing_buffer, size_t backing_buffer_len
) {
  a->buf         = (AllocatorArenaBuf *)backing_buffer;
  a->buf_len     = backing_buffer_len;
  a->curr_offset = 0;
  a->prev_offset = 0;
}

void *allocator_arena_alloc(AllocatorArena *a, void *ptr, size_t size) {
  unsigned char *old_mem = (unsigned char *)ptr;
  ptrdiff_t curr_ptr;
  ptrdiff_t offset;

  if(!allocator_is_power_of_two(ALLOCATOR_DEFAULT_ALIGNMENT)) {
    return NULL;
  }

  /* A zero size frees the block, following the realloc contract */
  if(size == 0) {
    allocator_arena_free(a, ptr);
    return NULL;
  }

  /* A NULL pointer bumps a fresh, aligned and zeroed block off the arena */
  if(old_mem == NULL) {
    curr_ptr = (ptrdiff_t)a->buf + (ptrdiff_t)a->curr_offset;
    offset   = allocator_align_forward(curr_ptr, ALLOCATOR_DEFAULT_ALIGNMENT);
    offset -= (ptrdiff_t)a->buf; /* Change to relative offset */

    /* Check to see if the backing memory has space left */
    if(offset + size <= a->buf_len) {
      void *mem      = &a->buf[offset];
      a->prev_offset = offset;
      a->curr_offset = offset + size;

      memset(mem, 0, size);
      return mem;
    }
    /* Return NULL if the arena is out of memory */
    return NULL;
  }

  /* Resizing is only valid for memory owned by this arena */
  if(a->buf <= old_mem && old_mem < a->buf + a->buf_len) {
    if(a->buf + a->prev_offset == old_mem) {
      /* The most recent allocation can grow or shrink in place */
      size_t old_size = a->curr_offset - a->prev_offset;
      a->curr_offset  = a->prev_offset + size;
      if(size > old_size) {
        /* Zero the grown region by default */
        memset(&a->buf[a->prev_offset + old_size], 0, size - old_size);
      }
      return old_mem;
    } else {
      /* Older allocations are moved to a fresh block.  The old size is
       * unknown, so the copy is clamped to what is left of the buffer */
      size_t available = (size_t)(a->buf + a->buf_len - old_mem);
      size_t copy_size = size < available ? size : available;
      void *new_memory = allocator_arena_alloc(a, NULL, size);
      if(new_memory != NULL) {
        memmove(new_memory, old_mem, copy_size);
      }
      return new_memory;
    }
  }

  return NULL;
}

void allocator_arena_free(AllocatorArena *a, void *ptr) {
  (void)a;
  (void)ptr;
}

void allocator_arena_free_all(AllocatorArena *a) {
  a->curr_offset = 0;
  a->prev_offset = 0;
}
