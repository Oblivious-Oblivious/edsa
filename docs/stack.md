# Stack

Dynamic stack implemented as macros over the vector. Start with a `NULL` pointer; the first push allocates storage.

## Include

```c
#include "edsa.h"
```

## API

| Macro                                             | Description                                              |
| ------------------------------------------------- | -------------------------------------------------------- |
| `stack_push(st, item)`                            | Push `item` onto the top (alias of `vector_push`)        |
| `stack_pop(st)`                                   | Pop and return the top; `0` when empty                   |
| `stack_peek(st)`                                  | Read the top element without removing it                 |
| `stack_size(st)`                                  | Number of elements on the stack                          |
| `stack_is_empty(st)`                              | True when `stack_size` is zero                           |
| `stack_free(st)`                                  | Release vector memory and set `st` to `NULL`             |
| `stack_set_allocator(st, ctx, alloc_fn, free_fn)` | Use a custom allocator (alias of `vector_set_allocator`) |

## Example

```c
#include "edsa.h"

#include <stdio.h>

int main(void) {
  int *st = NULL;
  unsigned char buf[256];
  AllocatorArena arena = {0};

  printf("empty: %d\n", stack_is_empty(st));
  printf("size: %zu\n", stack_size(st));

  allocator_arena_init(&arena, buf, sizeof(buf));
  stack_set_allocator(st, &arena, allocator_arena_alloc, NULL);

  stack_push(st, 2);
  stack_push(st, 3);
  stack_push(st, -1);

  printf("size: %zu\n", stack_size(st));
  printf("pop: %d\n", stack_pop(st));
  printf("pop: %d\n", stack_pop(st));
  printf("peek: %d\n", stack_peek(st));
  printf("pop: %d\n", stack_pop(st));
  printf("empty: %d\n", stack_is_empty(st));

  stack_free(st);

  return 0;
}
```
