#include "arena.h"

#include "../boolean/boolean.h"
#include "../preprocessor/preprocessor.h"

#include <assert.h> /* assert */
#include <string.h> /* memset */

p_inline bool is_power_of_two(ptrdiff_t x) { return (x & (x - 1)) == 0; }

p_inline ptrdiff_t align_forward(ptrdiff_t ptr, size_t align) {
  ptrdiff_t p, a, modulo;

  assert(is_power_of_two(align));

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

void allocator_arena_init(
  AllocatorArena *a, void *backing_buffer, size_t backing_buffer_len
) {
  a->buf         = (AllocatorArenaBuf *)backing_buffer;
  a->buf_len     = backing_buffer_len;
  a->curr_offset = 0;
  a->prev_offset = 0;
}

void *allocator_arena_resize(
  AllocatorArena *a, void *old_memory, size_t old_size, size_t new_size
) {
  unsigned char *old_mem = (unsigned char *)old_memory;

  assert(is_power_of_two(ALLOCATOR_ARENA_DEFAULT_ALIGNMENT));

  if(old_mem == NULL || old_size == 0) {
    return allocator_arena_alloc(a, new_size);
  } else if(a->buf <= old_mem && old_mem < a->buf + a->buf_len) {
    if(a->buf + a->prev_offset == old_mem) {
      a->curr_offset = a->prev_offset + new_size;
      if(new_size > old_size) {
        /* Zero the new memory by default */
        memset(&a->buf[a->curr_offset], 0, new_size - old_size);
      }
      return old_memory;
    } else {
      void *new_memory = allocator_arena_alloc(a, new_size);
      size_t copy_size = old_size < new_size ? old_size : new_size;
      /* Copy across old memory to the new memory */
      memmove(new_memory, old_memory, copy_size);
      return new_memory;
    }
  } else {
    assert(0 && "Memory is out of bounds of the buffer in this arena");
    return NULL;
  }
}

void *allocator_arena_alloc(AllocatorArena *a, size_t size) {
  /* Align 'curr_offset' forward to the specified alignment */
  ptrdiff_t curr_ptr = (ptrdiff_t)a->buf + (ptrdiff_t)a->curr_offset;
  ptrdiff_t offset = align_forward(curr_ptr, ALLOCATOR_ARENA_DEFAULT_ALIGNMENT);
  offset -= (ptrdiff_t)a->buf; /* Change to relative offset */

  /* Check to see if the backing memory has space left */
  if(offset + size <= a->buf_len) {
    void *ptr      = &a->buf[offset];
    a->prev_offset = offset;
    a->curr_offset = offset + size;

    /* Zero new memory by default */
    memset(ptr, 0, size);
    return ptr;
  }
  /* Return NULL if the arena is out of memory (or handle differently) */
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
