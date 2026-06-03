# Preprocessor

Compile-time macros for C standard detection, variadic counting, and related metaprogramming.

## Include

```c
#include "edsa.h"
```

## Common macros

| Macro                                             | Description                                       |
| ------------------------------------------------- | ------------------------------------------------- |
| `PREPROCESSOR_C_VERSION`                          | Detected C standard (e.g. `1999`, `2011`, `2023`) |
| `PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(...)` | Count variadic arguments (C99+)                   |
| `PREPROCESSOR_GNU`                                | Defined on GCC, Clang, and compatible compilers   |
| `PREPROCESSOR_32_BIT`                             | `1` on 32-bit platforms, else `0`                 |

See `src/preprocessor/preprocessor.h` for the full macro set.

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  printf("C version: %d\n", PREPROCESSOR_C_VERSION);
  printf("%d\n", PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(a, b, c)); /* 3 */
}
```
