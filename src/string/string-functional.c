#include "string-functional.h"

#include "string-base.h"

char *string_iterate(char *self, EdsaStringLambda apply) {
  size_t i;
  if(apply == NULL) {
    return self;
  }
  for(i = 0; i < string_size(self); i++) {
    apply(self[i]);
  }
  return self;
}

char *string_map(char *self, EdsaStringLambda modifier) {
  if(self == NULL || modifier == NULL) {
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
