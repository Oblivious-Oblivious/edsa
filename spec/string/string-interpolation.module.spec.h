#ifndef __EDSA_STRING_INTERPOLATION_MODULE_SPEC_H_
#define __EDSA_STRING_INTERPOLATION_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/string/estring.h"

module(T_string_interpolation, {
  describe("string interpolation", {
    it("displays a null string", {
      char *str = NULL;
      string_puts(str);
    });

    it("displays an empty string", {
      char *str = string_new("");
      string_puts(str);
      string_free(str);
    });

    it("displays a string", {
      char *str = string_new("test");
      string_puts(str);
      string_free(str);
    });
  });
})

#endif
