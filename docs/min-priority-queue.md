# Min Priority Queue (Binary Heap)

Min-heap priority queue built on the dynamic vector. Element type must support `<` (e.g. `int *` storing integers).

## Include

```c
#include "edsa.h"
```

## API

| Macro                   | Description                                                       |
| ----------------------- | ----------------------------------------------------------------- |
| `pq_insert(pq, key)`    | Append `key` and sift up to restore the min-heap property         |
| `pq_get_min(pq)`        | Return the smallest element (`pq[0]`), or `NULL` / 0 if empty     |
| `pq_delete_min(pq)`     | Remove the minimum, move the last leaf to the root, and sift down |
| `pq_size(pq)`           | Number of elements (alias of `vector_size`)                       |
| `pq_is_empty(pq)`       | True when the queue has no elements                               |
| `pq_reset(pq)`          | Clear all elements but keep allocated capacity                    |
| `pq_print(pq)`          | Print each element to stdout (debug helper)                       |
| `pq_free(pq)`           | Free backing storage (alias of `vector_free`)                     |
| `pq_set_allocator(...)` | Attach a custom allocator (alias of `vector_set_allocator`)       |

## Example

```c
#include "edsa.h"

#include <stdio.h>

int main(void) {
  int *pq = NULL;
  unsigned char buf[256];
  AllocatorArena arena = {0};

  printf("empty: %d\n", pq_is_empty(pq));
  printf("size: %zu\n", pq_size(pq));

  allocator_arena_init(&arena, buf, sizeof(buf));
  pq_set_allocator(pq, &arena, allocator_arena_alloc, NULL);

  pq_insert(pq, 30);
  pq_insert(pq, 10);
  pq_insert(pq, 20);

  printf("size: %zu\n", pq_size(pq));
  printf("min: %d\n", pq_get_min(pq));
  pq_print(pq);

  pq_delete_min(pq);
  printf("min after pop: %d\n", pq_get_min(pq));

  pq_reset(pq);
  printf("empty after reset: %d\n", pq_is_empty(pq));

  pq_insert(pq, 5);
  printf("min after reset: %d\n", pq_get_min(pq));

  pq_free(pq);

  return 0;
}
```
