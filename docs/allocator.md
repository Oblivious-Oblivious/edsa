# Allocator

Pluggable allocation strategies and helpers used by data structures.

## Include

```c
#include "edsa.h"
```

## Common interface

| Type / callback      | Description                                                                  |
| -------------------- | ---------------------------------------------------------------------------- |
| `allocator_alloc_fn` | Allocate (`ptr == NULL`), grow (`size > 0`), or free a block (`size == 0`)   |
| `allocator_free_fn`  | Optional teardown for a whole container (e.g. free every string in a vector) |

Wire allocators through `*_set_allocator` on supported types (`vector_set_allocator`, `stack_set_allocator`, `table_set_allocator`, etc.). Pass `allocator_arena_alloc` or `allocator_pool_alloc` as `alloc_fn`.

## Arena

Linear bump allocator over a fixed backing buffer. Reset the arena to reclaim everything.

| Function                                 | Description                                            |
| ---------------------------------------- | ------------------------------------------------------ |
| `allocator_arena_init(a, buf, len)`      | Bind the arena to a caller-owned buffer                |
| `allocator_arena_alloc(self, ptr, size)` | Bump-allocate, grow in place, or free when `size == 0` |
| `allocator_arena_free(self, ptr)`        | No-op; arena memory is not freed per block             |
| `allocator_arena_free_all(a)`            | Reset bump offsets so the buffer can be reused         |

## Pool

Fixed-size chunk allocator backed by a free list. Each request must fit in `chunk_size`.

| Function                                                  | Description                                           |
| --------------------------------------------------------- | ----------------------------------------------------- |
| `allocator_pool_init(p, buf, len, chunk_size, alignment)` | Prepare chunks from a backing buffer                  |
| `allocator_pool_alloc(self, ptr, size)`                   | Hand out a zeroed chunk, grow, or return when freeing |
| `allocator_pool_free(self, ptr)`                          | Push one chunk back onto the free list                |
| `allocator_pool_free_all(p)`                              | Return every chunk to the free list                   |

## Reference counting

Lightweight refcount wrapper with a user-supplied destructor.

| Function / macro                       | Description                                                |
| -------------------------------------- | ---------------------------------------------------------- |
| `allocator_rc_alloc(counted, free_fn)` | Initialize with reference count 1 and a destructor         |
| `allocator_rc_use(counted)`            | Increment the reference count                              |
| `allocator_rc_release(obj, counted)`   | Decrement; run `free_fn` on `obj` when the count reaches 0 |

## Utils

| Macro                         | Description                              |
| ----------------------------- | ---------------------------------------- |
| `ALLOCATOR_DEFAULT_ALIGNMENT` | Default alignment (`2 * sizeof(void *)`) |

## Example

```c
#include "edsa.h"

#include <stdio.h>

static void rc_free_string(void *obj) {
  char *str = (char *)obj;
  string_free(str);
}

int main(void) {
  unsigned char arena_buf[2048];
  AllocatorArena arena = {0};
  void *block          = NULL;

  unsigned char pool_buf[256];
  AllocatorPool pool = {0};
  void *chunk        = NULL;

  AllocatorRc counted = {0};
  char *shared        = string_new("shared");

  /* Arena */
  allocator_arena_init(&arena, arena_buf, sizeof(arena_buf));
  block = allocator_arena_alloc(&arena, NULL, 64);
  printf("before arena free     : offset=%zu\n", arena.curr_offset);
  allocator_arena_free(&arena, block);
  printf("after arena free      : offset=%zu\n", arena.curr_offset);
  allocator_arena_free_all(&arena);
  printf("after arena free_all  : offset=%zu\n", arena.curr_offset);

  /* Pool */
  printf("\n");
  allocator_pool_init(
    &pool, pool_buf, sizeof(pool_buf), 32, ALLOCATOR_DEFAULT_ALIGNMENT
  );
  chunk = allocator_pool_alloc(&pool, NULL, 32);
  printf("before pool free     : head=%p\n", (void *)pool.head);
  allocator_pool_free(&pool, chunk);
  printf("after pool free      : head=%p\n", (void *)pool.head);
  allocator_pool_free_all(&pool);
  printf("after pool free_all  : head=%p\n", (void *)pool.head);

  /* Reference counting */
  printf("\n");
  allocator_rc_alloc(&counted, rc_free_string);
  allocator_rc_use(&counted);
  allocator_rc_use(&counted);
  printf("before rc release: count=%td shared=%p\n", counted.count, shared);
  allocator_rc_release(shared, &counted);
  allocator_rc_release(shared, &counted);
  printf("after rc release : count=%td shared=%p\n", counted.count, shared);

  return 0;
}
```
