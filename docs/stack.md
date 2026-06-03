# Stack

Dynamic stack implemented as macros over the vector. Start with a `NULL` pointer; the first push grows storage automatically.

## Include

```c
#include "edsa.h"
```

## API

| Macro                      | Description                     |
| -------------------------- | ------------------------------- |
| `stack_push(st, item)`     | Push onto the top               |
| `stack_pop(st)`            | Pop and return top (0 if empty) |
| `stack_peek(st)`           | View top without popping        |
| `stack_size(st)`           | Number of elements              |
| `stack_is_empty(st)`       | True when empty                 |
| `stack_free(st)`           | Release memory                  |
| `stack_set_allocator(...)` | Custom allocator (via vector)   |

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  int *st = NULL;

  stack_push(st, 2);
  stack_push(st, 3);
  stack_push(st, -1);

  printf("item %d, should be -1\n", stack_pop(st));
  printf("item %d, should be 3\n", stack_pop(st));
  printf("peek item %d should be 2\n", stack_peek(st));
  printf("item %d, should be 2\n", stack_pop(st));

  stack_free(st);
}
```
