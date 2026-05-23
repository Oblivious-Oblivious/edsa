#include "file-handler.h"

void file_handler_init(EdsaFileHandler *self) {
  self->filepath = NULL;
  self->fd       = NULL;
}

bool file_handler_open(
  EdsaFileHandler *self, const char *name, const char *mode
) {
  self->filepath = name;
  self->fd       = fopen(self->filepath, mode);
  return self->fd == NULL ? false : true;
}

char *file_handler_read(const char *filepath) {
  EdsaFileHandler self = {0};
  file_handler_init(&self);

  if(!file_handler_open(&self, filepath, "r")) {
    file_handler_close(&self);
    return NULL;
  } else {
    char ch;
    char *result = string_new("");

    while((ch = fgetc(self.fd)) != EOF) {
      string_addf(&result, "%c", ch);
    }

    file_handler_close(&self);
    return result;
  }
}

void file_handler_write(const char *filename, const char *str) {
  FILE *f;
  char *mode;
  EdsaFileHandler self = {0};
  if((f = fopen(filename, "r"))) {
    mode = "a";
    fclose(f);
  } else {
    mode = "w";
  }
  file_handler_init(&self);
  file_handler_open(&self, filename, mode);
  fprintf(self.fd, "%s", str);
  file_handler_close(&self);
}

void file_handler_write_line(const char *filename, const char *line) {
  file_handler_write(filename, line);
  file_handler_write(filename, "\n");
}

void file_handler_close(EdsaFileHandler *self) {
  if(self) {
    fclose(self->fd);
  }
}

void file_handler_deinit(EdsaFileHandler *self) {
  file_handler_close(self);
  self->fd       = NULL;
  self->filepath = NULL;
}
