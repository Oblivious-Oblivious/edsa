#include "string-editing.h"

#include "../vector/vector.h"
#include "string-base.h"
#include "string-dup.h"

char **string_split(char *self, const char delimeter) {
  char **str_tokens = NULL;
  char *tmp         = NULL;
  char *empty       = string_new("");

  if(self == NULL) {
    string_free(empty);
    return NULL;
  } else if(string_equals(self, empty)) {
    string_free(empty);
    vector_add(str_tokens, string_new(""));
  } else if(string_size(self) == 1 && self[0] == delimeter) {
    string_free(empty);
    vector_add(str_tokens, string_new(""));
    vector_add(str_tokens, string_new(""));
  } else {
    size_t i;
    string_free(empty);
    tmp = string_new("");
    for(i = 0; i < string_size(self); i++) {
      if(self[i] == delimeter) {
        vector_add(str_tokens, tmp);
        tmp = string_new("");
      } else {
        string_addf(&tmp, "%c", self[i]);
      }
    }

    if(tmp != NULL && string_size(tmp) > 0) {
      vector_add(str_tokens, tmp);
    } else {
      string_free(tmp);
    }
  }

  return str_tokens;
}

char *
string_substring(char *self, ptrdiff_t from_position, ptrdiff_t to_position) {
  char *strdup = NULL;

  if(self == NULL) {
    return NULL;
  }

  strdup = string_dup(self);

  if(to_position < 0) {
    string_ignore_last(strdup, -to_position);
  } else {
    string_shorten(strdup, to_position);
  }

  if(from_position < 0) {
    string_skip_first(strdup, string_size(self) + from_position);
  } else {
    string_skip_first(strdup, from_position);
  }

  return strdup;
}

char *string_remove_underscores(char *self) {
  size_t i;
  for(i = 0; i < string_size(self); i++) {
    if(self[i] == '_') {
      string_remove(self, i);
      i--;
    }
  }
  return self;
}
