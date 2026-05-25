#include "string-base.h"

#include <limits.h> /* INT_MAX */
#include <stdio.h>  /* vsnprintf */

char *string_new(const char *initial_string) {
  char *self = NULL;
  string_add(self, initial_string);
  return self;
}

void string_add_(char **self, const char *other) {
  if(other == NULL) {
    return;
  } else {
    string_addn(*self, other, strlen(other));
  }
}

void string_addi_(char **self, const char *other) {
  if(other == NULL) {
    return;
  } else {
    string_addn(*self, other, string_size(other));
  }
}

void string_addf(char **self, const char *f, ...) {
  signed int result = 0;
  /* TODO - Bounds checks */
  char buf[4096];
  va_list args;

  va_start(args, f)
    ;
    result = vsnprintf(buf, sizeof(buf), f, args);
  va_end(args);

  if(result >= 0) {
    string_add(*self, buf);
  }
}

size_t string_size(const char *self) { return vector_size(self); }

size_t string_size_signed(char *self) { return vector_size_signed(self); }

void string_shorten(char *self, size_t len) {
  if(self != NULL) {
    if((ptrdiff_t)len < 0) {
      _vector_get_header(self)->size = 0;
    } else if((ptrdiff_t)len < vector_size_signed(self)) {
      _vector_get_header(self)->size = (ptrdiff_t)len;
    }
    self[string_size(self)] = '\0';
  }
}

void string_skip_first(char *self, size_t len) {
  if(self != NULL) {
    if((ptrdiff_t)len >= vector_size_signed(self)) {
      string_delete(self);
    } else if((ptrdiff_t)len > 0) {
      _vector_get_header(self)->size -= (ptrdiff_t)len;
      memmove(self, self + (ptrdiff_t)len, string_size(self));
      self[string_size(self)] = '\0';
    }
  }
}

void string_ignore_last(char *self, size_t len) {
  if(self == NULL) {
    return;
  }
  if((ptrdiff_t)len < 0) {
    return;
  }
  if(len >= string_size(self)) {
    string_shorten(self, 0);
  } else {
    string_shorten(self, string_size(self) - len);
  }
}

void string_delete(char *self) { string_shorten(self, 0); }

void string_remove(char *self, size_t pos) {
  if(self == NULL || pos >= string_size(self)) {
    return;
  } else {
    vector_remove(self, pos);
    self[string_size(self)] = '\0';
  }
}

bool string_equals(char *self, const char *other) {
  if(self == NULL || other == NULL) {
    return false;
  } else {
    return (
      string_size(self) == strlen(other) &&
      strncmp(self, other, string_size(self)) == 0
    );
  }
}

void string_free_(char **self) {
  vector_free(*self);
  *self = NULL;
}
