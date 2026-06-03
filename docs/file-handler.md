# File Handler

Helpers for reading and writing files.

## Include

```c
#include "edsa.h"
```

## API

| Function                                  | Description                                             |
| ----------------------------------------- | ------------------------------------------------------- |
| `file_handler_read(filepath)`             | Read an entire file into a new string; caller frees     |
| `file_handler_write(filename, str)`       | Append to an existing file or create and write a string |
| `file_handler_write_line(filename, line)` | Write a line and append `\n`                            |

`file_handler_read` allocates a new edsa string on success. Free it with
`string_free` when you are done.

## Example

```c
#include "edsa.h"

#include <stdio.h>

int main(void) {
  char *contents = NULL;

  file_handler_write("demo.txt", "first line");

  contents = file_handler_read("demo.txt");
  if(contents) {
    printf("after create: `%s`\n", contents);
    string_free(contents);
  }

  file_handler_write_line("demo.txt", "second line");
  /* adds a newline as well */
  file_handler_write_line("demo.txt", "third line");

  contents = file_handler_read("demo.txt");
  if(contents) {
    printf("after append: `%s`\n", contents);
    string_free(contents);
  }

  return 0;
}
```
