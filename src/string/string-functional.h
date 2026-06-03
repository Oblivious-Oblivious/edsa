#ifndef __EDSA_STRING_FUNCTIONAL_H_
#define __EDSA_STRING_FUNCTIONAL_H_

#include "../vector/vector.h"
#include "string-base.h"

#include <stdarg.h>
#include <stdio.h>

#if PREPROCESSOR_C_VERSION >= 1999
  #define string_puts(...)                                                 \
    string_display(                                                        \
      PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(__VA_ARGS__), __VA_ARGS__ \
    )

/**
 * @brief Used for string interpolation
 * @param argc -> The number of the arguments provided by the macros
 * @param __VA_ARGS__ -> The rest of the arguments to iterate through
 **/
p_inline void string_display(size_t argc, ...) {
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

/**
 * @brief A generic function type used upon iterable data structures
 * @param -> An element belonging to an iterable
 * @return -> A value that satisfies the callee's purpose (map, filter, reduce)
 **/
/* The param void* can have more than 1 argument stored as a list of some sort
 */
/* Since this is completely generic we can't check for validity of arguments */
/* The validity of the function is dependent on the callee */
typedef char (*EdsaStringLambda)(char);

/**
 * @brief Iterates through the characters of the string
 * @param self -> The string builder we want to iterate
 * @param apply -> The function we apply to each character
 **/
char *string_iterate(char *self, EdsaStringLambda apply);

/**
 * @brief Maps each character of the string according to a modifier function
 * @param self -> The string builder to map
 * @param modifier -> The EdsaStringLambda function to use for the
 *conversions
 * @return A new mapped string
 **/
char *string_map(char *self, EdsaStringLambda modifier);

#endif
