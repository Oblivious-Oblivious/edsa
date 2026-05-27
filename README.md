# edsa

A collection of basic data structures for C.

## Installation

**Install [Emeralds](https://github.com/Oblivious-Oblivious/Emeralds) package manager**

## Compile the library

```sh
em list
em install
em build lib release
```

## Compile your code

```sh
# requires the edsa static library included in the export folder along with edsa.h
clang export/edsa.a your-code.c
```

## Usage

### Boolean

```c
#include "edsa.h"

int main(void) {
  bool value = true;
  bool fvalue = false;
  if(value) {
    if(!fvalue) {
      printf("%s\n", "42");
    }
  }
}
```

### Fast Stack

```c
#include "edsa.h"

int main(void) {
  fs_push(st, 42);
  int res = fs_pop(st);
  printf("%d\n", res);
}
```

### File Handler

```c
#include "edsa.h"

int main(void) {
  char *line1;
  char *line2;
  struct EdsaFileHandler *h = file_handler_new();

  if(read_handler_open(h, "file.txt")) {
    line1 = read_handler_read_line();
    line2 = read_handler_read_line();
  }

  printf("%s\n", line1);
  printf("%s\n", line2);

  free(line1);
  free(line2);

  read_handler_close(h);
}
```

### Linked List

```c
#include "edsa.h"

int main(void) {
  EdsaLinkedList *l = linked_list_new();

  linked_list_add(l, (void*)1);
  linked_list_add(l, (void*)2);

  linked_list_remove(l, (void*)1);

  linked_list_free(l);
}
```

### Min Priority Queue (Binary Heap)

```c
#include "edsa.h"

int main(void) {
  EdsaMinPQBinaryHeap *pq = pq_new(10);

  pq_insert(pq, (void*)30);
  pq_insert(pq, (void*)10);
  pq_insert(pq, (void*)20);

  void *min = pq_get_min(pq);
  printf("%ld\n", (long)min); /* 10 */

  pq_delete_min(pq);
  printf("%ld\n", (long)pq_get_min(pq)); /* 20 */

  pq_free(pq);
}
```

### Preprocessor

```c
#include "edsa.h"

int main(void) {
  /* Detect the C standard version at compile time */
  printf("C version: %d\n", PREPROCESSOR_C_VERSION);

  /* Count the number of variadic arguments (C99+) */
  printf("%d\n", PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(a, b, c)); /* 3 */
}
```

### Stack

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  EdsaStack *st = stack_new();
  stack_push(st, 2);
  stack_push(st, 3);
  stack_push(st, -1);
  printf("item %d, should be -1\n", stack_pop(st));
  printf("item %d, should be 3\n", stack_pop(st));
  printf("peek item %d should be 2\n", stack_peek(st));
  printf("item %d, should be 2\n", stack_pop(st));
}
```

### String

```c
#include "edsa.h"

int main(void) {
  char *str = string_new("test");
  printf("%s\n", str);
  string_free(str);
}
```

### Table

```c
#include "edsa.h"

int main(void) {
  EdsaTable *t = table_new();
  table_add(t, "key1", 100);
  table_add(t, "key2", 200);
  table_add(t, "key3", 300);

  size_t value1 = table_get(t, "key1");
  size_t value2 = table_get(t, "key2");
  size_t value3 = table_get(t, "key3");
  size_t value4 = table_get(t, "key4");

  printf("%zu\n", value1);
  printf("%zu\n", value2);
  printf("%zu\n", value3);
  printf("%zu\n", value4);
}
```

### Vector

```c
#include "edsa.h"

int main(void) {
  int **v = vector_new(1);

  vector_add(v, 2);
  vector_add(v, 3);

  printf("%d\n", v[1]);
  printf("%d\n", v[0]);
}
```

## Contributing

1. Fork it (<https://github.com/Oblivious-Oblivious/edsa/fork>)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

## Contributors

- [atha](https://github.com/Oblivious-Oblivious) - creator and maintainer
