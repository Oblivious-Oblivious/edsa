# File Handler

Helpers for opening, reading, writing, and closing files.

## Include

```c
#include "edsa.h"
```

## Types

- `EdsaFileHandler` — holds `FILE *fd` and `const char *filepath`

## API

| Function                                  | Description                                       |
| ----------------------------------------- | ------------------------------------------------- |
| `file_handler_init(self)`                 | Zero-initialize a handler                         |
| `file_handler_open(self, name, mode)`     | Open a file; returns `true` on success            |
| `file_handler_read(filepath)`             | Read entire file into a new string (caller frees) |
| `file_handler_write(filename, str)`       | Append or create and write a string               |
| `file_handler_write_line(filename, line)` | Write a line with a trailing newline              |
| `file_handler_close(self)`                | Close the open `FILE *`                           |
| `file_handler_deinit(self)`               | Close and clear handler fields                    |

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  char *contents = file_handler_read("file.txt");
  if(contents) {
    printf("%s\n", contents);
    string_free(contents);
  }

  file_handler_write_line("out.txt", "hello");
}
```
