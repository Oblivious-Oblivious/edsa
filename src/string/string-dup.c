#include "string-dup.h"

#include "string-base.h"

char *string_dup(char *self) {
  char *dup = NULL;
  string_add(dup, self);
  return dup;
}
