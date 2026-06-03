# Allocator

Pluggable allocation strategies and helpers used by data structures.

## Include

```c
#include "edsa.h"
```

## Common interface

```c
typedef void *(*allocator_alloc_fn)(void *allocator, void *ptr, size_t size);
typedef void (*allocator_free_fn)(void *allocator, void *self);
```

Pass `allocator_arena_alloc` or `allocator_pool_alloc` as `alloc_fn`, and optional custom `free_fn` callbacks, via `*_set_allocator` on supported types (e.g. `vector_set_allocator`, `stack_set_allocator`, `table_set_allocator`).

`alloc_fn(self, NULL, size)` allocates; `alloc_fn(self, ptr, new_size)` grows; `alloc_fn(self, ptr, 0)` frees a block.

## Arena

Linear bump allocator over a fixed backing buffer. Fast allocations; individual frees are no-ops until you reset the whole arena.

| Function                                 | Description                                  |
| ---------------------------------------- | -------------------------------------------- |
| `allocator_arena_init(a, buf, len)`      | Bind arena to a buffer                       |
| `allocator_arena_alloc(self, ptr, size)` | Allocate / grow / free                       |
| `allocator_arena_free(self, ptr)`        | No-op (arena does not reclaim single blocks) |
| `allocator_arena_free_all(a)`            | Reset offsets to reuse the buffer            |

## Pool

Fixed-size chunk allocator with a free list. Requests must fit in `chunk_size`.

| Function                                                  | Description                       |
| --------------------------------------------------------- | --------------------------------- |
| `allocator_pool_init(p, buf, len, chunk_size, alignment)` | Set up pool                       |
| `allocator_pool_alloc(self, ptr, size)`                   | Take or return a chunk            |
| `allocator_pool_free(self, ptr)`                          | Return chunk to free list         |
| `allocator_pool_free_all(p)`                              | Reset all chunks to the free list |

## Reference counting

Lightweight refcount wrapper with a user-supplied destructor.

| Function / macro                       | Description                                 |
| -------------------------------------- | ------------------------------------------- |
| `allocator_rc_alloc(counted, free_fn)` | Start with count 1                          |
| `allocator_rc_use(counted)`            | Increment count                             |
| `allocator_rc_release(obj, counted)`   | Decrement; call `free_fn` when count hits 0 |

## Utils

| Function / macro                            | Description                          |
| ------------------------------------------- | ------------------------------------ |
| `ALLOCATOR_DEFAULT_ALIGNMENT`               | Default alignment (2 × pointer size) |
| `allocator_is_power_of_two(x)`              | Power-of-two test                    |
| `allocator_align_forward(ptr, align)`       | Align a uintptr_t                    |
| `allocator_align_forward_size(size, align)` | Align a size                         |

## Example (arena-backed stack)

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  unsigned char buffer[2048];
  AllocatorArena arena;
  int *st = NULL;

  allocator_arena_init(&arena, buffer, sizeof(buffer));
  stack_set_allocator(st, &arena, allocator_arena_alloc, NULL);

  stack_push(st, 10);
  stack_push(st, 20);
  printf("%d\n", stack_pop(st));

  stack_free(st);
  allocator_arena_free_all(&arena);
}
```
