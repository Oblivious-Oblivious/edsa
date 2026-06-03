# Vector

Generic dynamic array. **Heavily** inspired by STB. Element type is inferred from the pointer (`int *`, `char **`, `void **`, etc.).

## Include

```c
#include "edsa.h"
```

## API

| Macro / function                                     | Description                                                             |
| ---------------------------------------------------- | ----------------------------------------------------------------------- |
| `vector_new(...)`                                    | Create a typed vector with initial elements (C11+; type from first arg) |
| `vector_initialize(self)`                            | Start as `NULL`; grow on first insert (C99 fallback)                    |
| `vector_initialize_n(self, n)`                       | Allocate `n` zeroed slots                                               |
| `vector_add(self, item)`                             | Append one element at the end                                           |
| `vector_push(self, item)`                            | Alias of `vector_add`                                                   |
| `vector_pop(self)`                                   | Remove and return the last element; `0` when empty                      |
| `vector_peek(self)`                                  | Last element without shrinking the vector                               |
| `vector_last(self)`                                  | Same slot as `peek`, as an lvalue                                       |
| `vector_size(self)`                                  | Number of elements                                                      |
| `vector_capacity(self)`                              | Allocated slot count                                                    |
| `vector_is_empty(self)`                              | True when `vector_size` is zero                                         |
| `vector_remove(self, index)`                         | Delete one element and shift later items down                           |
| `vector_remove_last(self)`                           | Delete the final element                                                |
| `vector_free(self)`                                  | Free storage (and optional item free hook); set pointer to `NULL`       |
| `vector_set_allocator(self, ctx, alloc_fn, free_fn)` | Plug in arena/pool/custom alloc before use                              |
| `vector_map / vector_filter / vector_reduce`         | Functional helpers over elements (see `vector.h`)                       |

`vector_new` requires C11+. On C99, use `vector_initialize` plus `vector_add`.

## Example

```c
#include "edsa.h"

#include <stdio.h>

/*
 * Minimum -std flags (see PREPROCESSOR_C_VERSION in preprocessor.h):
 *   -std=c99  — vector_initialize, vector_initialize_n, map/filter/reduce
 *   -std=c11  — vector_new
 */

static int double_item(int item) { return item * 2; }

static int drop_above_two(int item) { return item > 2; }

static int sum_items(int acc, int curr) { return acc + curr; }

int main(void) {
  unsigned char buf[512];
  AllocatorArena arena = {0};
  int *empty           = NULL;
  int *v               = NULL;
  int *init            = NULL;
  int *zeroed          = NULL;
  int *mapped          = NULL;
  int *filtered        = NULL;
#if PREPROCESSOR_C_VERSION >= 1999
  int sum = 0;
#endif

  printf("empty: %d\n", vector_is_empty(empty));

#if PREPROCESSOR_C_VERSION >= 2011
  v = vector_new(1, 2, 3, 4, 5);
#else
  vector_initialize(v);
  vector_add(v, 1);
  vector_add(v, 2);
  vector_add(v, 3);
  vector_add(v, 4);
  vector_add(v, 5);
#endif
  printf("size: %zu capacity: %zu\n", vector_size(v), vector_capacity(v));

  allocator_arena_init(&arena, buf, sizeof(buf));
  vector_set_allocator(v, &arena, allocator_arena_alloc, NULL);

  vector_add(v, 6);
  vector_push(v, 7);

  printf("peek: %d last: %d\n", vector_peek(v), vector_last(v));
  printf("pop: %d\n", vector_pop(v));

#if PREPROCESSOR_C_VERSION >= 1999
  vector_map(v, mapped, double_item);
  vector_filter(v, filtered, drop_above_two);
  vector_reduce(v, sum_items, &sum);
  printf(
    "mapped[0]: %d\nfiltered size: %zu\nsum: %d\n",
    mapped[0],
    vector_size(filtered),
    sum
  );
#else
  printf("map/filter/reduce: (requires -std=c99+)\n");
#endif

  vector_remove(v, 0);
  vector_remove_last(v);
  printf("size: %zu\n", vector_size(v));

#if PREPROCESSOR_C_VERSION >= 1999
  vector_initialize(init);
  vector_add(init, 10);
  vector_initialize_n(zeroed, 3);
  printf("init[0]: %d zeroed slots: %zu\n", init[0], vector_size(zeroed));
#else
  printf("vector_initialize*: (requires -std=c99+)\n");
#endif

  vector_free(v);
  vector_free(init);
  vector_free(zeroed);
  vector_free(mapped);
  vector_free(filtered);

  return 0;
}
```
