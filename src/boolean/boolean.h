#ifndef __EDSA_BOOLEAN_H_
#define __EDSA_BOOLEAN_H_

#include "../preprocessor/preprocessor.h"

/** @param bool -> A 'big' enough size to hold both 1 and 0 **/
#if PREPROCESSOR_C_VERSION < 2023
  #define bool  unsigned char
  #define true  1
  #define false 0
#else
  #include <stdbool.h>
#endif

#endif
