# Vector

Generic dynamic array (stretchy buffer). Type is inferred from the pointer you use (`int *`, `char **`, `void **`, etc.).

## Include

```c
#include "edsa.h"
```

## API

| Macro                     | Description                                              |
| ------------------------- | -------------------------------------------------------- |
| `vector_new(...)`         | Create with initial elements (C11+; type from first arg) |
| `vector_add(self, item)`  | Append one element                                       |
| `vector_push(self, item)` | Alias for `vector_add`                                   |
| `vector_pop(self)`        | Remove and return last                                   |
| `vector_peek(self)`       | Last element without removing                            |
| `vector_size(self)`       | Element count                                            |
| `vector_free(self)`       | Release memory                                           |

Requires C11 or later for `vector_new`. On C99, use `vector_initialize(self)` and `vector_add` instead.

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  int *v = vector_new(2, 3);

  vector_add(v, 4);

  printf("%d\n", v[0]); /* 2 */
  printf("%d\n", v[1]); /* 3 */
  printf("%d\n", v[2]); /* 4 */

  vector_free(v);
}
```
