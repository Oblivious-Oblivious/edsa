#include "string-functional.h"

#include "string-base.h"

#include <stdio.h> /* printf */

#if PREPROCESSOR_C_VERSION >= 1999
void string_display(size_t argc, ...) {
  size_t i;
  char *self = string_new("");

  va_list vars;
  va_start(vars, argc)
    ;
    for(i = 0; i < argc; i++) {
      char *v = va_arg(vars, char *);
      if(v != NULL) {
        string_add(self, v);
      }
    }
  va_end(vars);

  printf("displaying: %s\n", self);
  string_free(self);
}
#endif

char *string_iterate(char *self, EdsaStringLambda apply) {
  size_t i;
  for(i = 0; i < string_size(self); i++) {
    apply(self[i]);
  }
  return self;
}

char *string_map(char *self, EdsaStringLambda modifier) {
  if(self == NULL) {
    return NULL;
  } else {
    size_t i;
    char *self_dup = string_new("");
    for(i = 0; i < string_size(self); i++) {
      string_addf(&self_dup, "%c", modifier(self[i]));
    }
    return self_dup;
  }
}
