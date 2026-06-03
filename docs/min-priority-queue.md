# Min Priority Queue (Binary Heap)

Min-heap priority queue built on the dynamic vector. Values must support `<` comparison (e.g. `int *`, `void **` used as integers).

## Include

```c
#include "edsa.h"
```

## API

| Macro                   | Description                                  |
| ----------------------- | -------------------------------------------- |
| `pq_insert(pq, key)`    | Insert and heapify up                        |
| `pq_get_min(pq)`        | Peek minimum (index 0), or `NULL`/0 if empty |
| `pq_delete_min(pq)`     | Remove minimum and restore heap              |
| `pq_size(pq)`           | Element count (alias of `vector_size`)       |
| `pq_is_empty(pq)`       | True when empty                              |
| `pq_free(pq)`           | Free backing storage                         |
| `pq_reset(pq)`          | Clear elements, keep capacity                |
| `pq_set_allocator(...)` | Custom allocator (via vector)                |

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  int *pq = NULL;

  pq_insert(pq, 30);
  pq_insert(pq, 10);
  pq_insert(pq, 20);

  printf("%d\n", pq_get_min(pq)); /* 10 */

  pq_delete_min(pq);
  printf("%d\n", pq_get_min(pq)); /* 20 */

  pq_free(pq);
}
```
