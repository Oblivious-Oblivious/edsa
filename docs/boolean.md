# Boolean

Portable `bool`, `true`, and `false` for pre-C23 compilers.

## Include

```c
#include "edsa.h"
```

## Behavior

When `PREPROCESSOR_C_VERSION < 2023`, edsa defines `bool` as `unsigned char` and `true`/`false` as `1`/`0`. On C23 and later, it includes `<stdbool.h>` instead.

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  bool value  = true;
  bool fvalue = false;

  if(value && !fvalue) {
    printf("%s\n", "42");
  }
}
```
