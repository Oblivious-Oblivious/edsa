# String

Growable string build type backed by the vector.

## Include

```c
#include "edsa.h"
```

## Base API

| Function / macro                | Description                                             |
| ------------------------------- | ------------------------------------------------------- |
| `string_new(initial)`           | Allocate a string initialized from a C string (or `""`) |
| `string_add(self, other)`       | Append another C string                                 |
| `string_addi(self, other)`      | Append without copying `other` (must outlive `self`)    |
| `string_addn(self, other, len)` | Append at most `len` bytes from `other`                 |
| `string_addf(&self, fmt, ...)`  | Append formatted output (`printf`-style)                |
| `string_size(self)`             | Length in bytes (excludes a trailing `NUL` if present)  |
| `string_shorten(self, len)`     | Truncate to `len` bytes from the start                  |
| `string_skip_first(self, len)`  | Drop `len` bytes from the beginning                     |
| `string_ignore_last(self, len)` | Drop `len` bytes from the end                           |
| `string_delete(self)`           | Clear contents but keep the allocation                  |
| `string_remove(self, pos)`      | Remove the character at index `pos`                     |
| `string_equals(self, other)`    | Compare contents; `true` when equal                     |
| `string_free(self)`             | Free storage (macro; pass the pointer variable by name) |
| `string_set_allocator(...)`     | Attach a custom allocator (via vector)                  |

## Editing API (`string-editing.h`)

| Function                           | Description                                       |
| ---------------------------------- | ------------------------------------------------- |
| `string_split(self, delimiter)`    | Split on `delimiter`; returns a `char **` vector  |
| `string_substring(self, from, to)` | Copy a slice `[from, to)` without mutating `self` |
| `string_remove_underscores(self)`  | Remove every `_` in place; returns `self`         |

## Functional API (`string-functional.h`, C99+)

| Function / macro           | Description                                    |
| -------------------------- | ---------------------------------------------- |
| `string_iterate(self, fn)` | Apply `fn` to each character in place          |
| `string_map(self, fn)`     | Return a new string with `fn` applied per char |
| `string_puts(...)`         | Debug-print variadic strings (C99+)            |

## Other

| Function          | Description                      |
| ----------------- | -------------------------------- |
| `string_dup(str)` | Return a heap duplicate of `str` |

## Example

```c
#include "edsa.h"

#include <stdio.h>

static char to_upper(char c) {
  if(c >= 'a' && c <= 'z') {
    return (char)(c - 'a' + 'A');
  } else {
    return c;
  }
}

int main(void) {
  char *str      = NULL;
  char *slice    = NULL;
  char *mapped   = NULL;
  char *copy     = NULL;
  char **parts   = NULL;
  char *csv      = NULL;
  char *tail_lit = NULL;
  unsigned char buf[512];
  AllocatorArena arena = {0};

  allocator_arena_init(&arena, buf, sizeof(buf));
  string_set_allocator(str, &arena, allocator_arena_alloc, NULL);
  string_add(str, "foo_bar");

  string_remove_underscores(str);
  string_add(str, ",");
  tail_lit = string_new("tail");
  string_addi(str, tail_lit);
  string_free(tail_lit);
  string_addn(str, "zzz", 1);
  string_addf(&str, ":%d", 7);

  printf("str: %s\n", str);
  printf("size: %zu\n", string_size(str));
  printf("equals: %d\n", string_equals(str, "foobar,tailz:7"));

  slice  = string_substring(str, 0, 6);
  mapped = string_map(slice, to_upper);
  printf("slice map: %s\n", mapped);

  csv   = string_new("a,b,c");
  parts = string_split(csv, ',');
  printf("split parts: %zu\n", vector_size(parts));

#if PREPROCESSOR_C_VERSION >= 1999
  string_puts("debug:", str);
  string_iterate(str, to_upper);
#endif

  string_skip_first(str, 1);
  string_ignore_last(str, 2);
  string_shorten(str, 8);
  string_remove(str, 2);

  string_delete(str);
  string_add(str, "done");

  copy = string_dup(str);
  printf("dup: %s\n", copy);

  string_free(slice);
  string_free(mapped);
  string_free(csv);
  string_free(parts[0]);
  string_free(parts[1]);
  string_free(parts[2]);
  vector_free(parts);
  string_free(copy);
  string_free(str);

  return 0;
}
```
