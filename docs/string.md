# String

Growable string type backed by the vector. Supports concatenation, formatting, and comparison.

## Include

```c
#include "edsa.h"
```

## API

| Function / macro               | Description                                |
| ------------------------------ | ------------------------------------------ |
| `string_new(initial)`          | Create a string from initial text          |
| `string_add(self, other)`      | Append another C string                    |
| `string_addf(&self, fmt, ...)` | Append formatted text                      |
| `string_size(self)`            | Length in bytes                            |
| `string_equals(self, other)`   | Compare contents                           |
| `string_free(self)`            | Free storage (macro; pass pointer by name) |

Additional helpers live in `string-editing.h`, `string-functional.h`, and `string-dup.h` (split, substring, dup, etc.).

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  char *str = string_new("test");
  printf("%s\n", str);
  string_free(str);
}
```
