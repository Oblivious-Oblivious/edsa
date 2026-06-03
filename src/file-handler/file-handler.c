#include "file-handler.h"

#include "../string/string-base.h"

#include <stdio.h>

char *file_handler_read(const char *filepath) {
  FILE *fd;
  int ch;
  char *result;

  if(filepath == NULL) {
    return NULL;
  }

  fd = fopen(filepath, "r");
  if(fd == NULL) {
    return NULL;
  }

  result = string_new("");
  while((ch = fgetc(fd)) != EOF) {
    string_addf(&result, "%c", ch);
  }

  fclose(fd);
  return result;
}

void file_handler_write(const char *filename, const char *str) {
  FILE *fd;
  FILE *probe;
  const char *mode;

  if(filename == NULL || str == NULL) {
    return;
  }
  if((probe = fopen(filename, "r"))) {
    mode = "a";
    fclose(probe);
  } else {
    mode = "w";
  }
  fd = fopen(filename, mode);
  if(fd == NULL) {
    return;
  }
  fprintf(fd, "%s", str);
  fclose(fd);
}

void file_handler_write_line(const char *filename, const char *line) {
  file_handler_write(filename, line);
  file_handler_write(filename, "\n");
}
