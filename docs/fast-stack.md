# Fast Stack

Macro-based stack operations on a raw pointer. No allocation; you provide the backing array and stack pointer.

## Include

```c
#include "edsa.h"
```

## API

| Macro                   | Description                                                 |
| ----------------------- | ----------------------------------------------------------- |
| `fs_push(sp, item)`     | Push onto the stack; advances `sp`                          |
| `fs_pop(sp)`            | Pop and return the top item; moves `sp` back                |
| `fs_peek(sp, distance)` | Read an item `distance` slots below the top without popping |

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  int st[65536];
  int *sp = st;

  fs_push(sp, 42);
  int res = fs_pop(sp);
  printf("%d\n", res);
}
```
