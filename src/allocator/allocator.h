#ifndef __EDSA_ALLOCATOR_H_
#define __EDSA_ALLOCATOR_H_

#include <stddef.h> /* size_t */

typedef void *(*allocator_alloc_fn)(void *allocator, void *ptr, size_t size);
typedef void (*allocator_free_fn)(void *allocator, void *self);

#endif
