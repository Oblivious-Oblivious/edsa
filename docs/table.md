# Table

Open-addressing hash table with linear probing. Keys are C strings; values are `size_t`. Use `table_init` on a stack-allocated `EdsaTable`.

## Include

```c
#include "edsa.h"
```

## API

| Function                      | Description                                  |
| ----------------------------- | -------------------------------------------- |
| `table_init(self)`            | Initialize buckets                           |
| `table_add(self, key, value)` | Insert or update                             |
| `table_get(self, key)`        | Lookup; returns `TABLE_UNDEFINED` if missing |
| `table_remove(self, key)`     | Delete a key                                 |
| `table_size(self)`            | Number of entries                            |
| `table_deinit(self)`          | Free internal vectors                        |
| `table_set_allocator(...)`    | Custom allocator                             |

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  EdsaTable t = {0};
  table_init(&t);

  table_add(&t, "key1", 100);
  table_add(&t, "key2", 200);
  table_add(&t, "key3", 300);

  printf("%zu\n", table_get(&t, "key1"));
  printf("%zu\n", table_get(&t, "key2"));
  printf("%zu\n", table_get(&t, "key3"));
  printf("%zu\n", table_get(&t, "key4")); /* TABLE_UNDEFINED */

  table_deinit(&t);
}
```
