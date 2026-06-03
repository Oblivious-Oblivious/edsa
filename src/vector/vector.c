#include "vector.h"

void *_vector_growf(
  void *self,
  size_t elemsize,
  size_t addlen,
  size_t min_cap,
  void *allocator,
  allocator_alloc_fn alloc
) {
  void *b;
  void *old_header;
  size_t total;
  size_t min_len = vector_size(self) + addlen;

  if(min_len > min_cap) {
    min_cap = min_len;
  }

  if(min_cap <= vector_capacity(self)) {
    return self;
  }

  if(min_cap < 2 * vector_capacity(self)) {
    min_cap = 2 * vector_capacity(self);
  } else if(min_cap < 4) {
    min_cap = 4;
  }

  old_header = (self) ? _vector_get_header(self) : 0;
  total      = elemsize * min_cap + sizeof(_vector_header);
  b = alloc ? alloc(allocator, old_header, total) : realloc(old_header, total);
  if(b == NULL) {
    return self;
  }
  b = (char *)b + sizeof(_vector_header);

  if(self == NULL) {
    _vector_get_header(b)->size      = 0;
    _vector_get_header(b)->allocator = allocator;
    _vector_get_header(b)->alloc     = alloc;
    _vector_get_header(b)->free      = NULL;
  }

  _vector_get_header(b)->capacity = min_cap;

  return b;
}

void _vector_add_n_helper(
  void *dest, const void *src, size_t n, size_t elem_size
) {
  if(src != NULL) {
    memmove(dest, src, n * elem_size);
  }
}
