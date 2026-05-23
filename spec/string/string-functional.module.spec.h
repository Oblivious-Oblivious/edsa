#ifndef __EDSA_STRING_FUNCTIONAL_MODULE_SPEC_H_
#define __EDSA_STRING_FUNCTIONAL_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/string/string.h"

static char iterator(char c) {
  printf("iterating: %c\n", c);
  return c;
}

static char map(char c) { return c + 1; }

module(T_string_functional, {
  describe("string functional functions", {
    context("on iterating", {
      it("iterates through a null string", {
        char *str = NULL;
        string_iterate(str, (EdsaStringLambda)iterator);
      });

      it("iterates through an empty string", {
        char *str = string_new("");
        string_iterate(str, (EdsaStringLambda)iterator);
        string_free(str);
      });

      it("iterates through a string", {
        char *str = string_new("oblivious");
        string_iterate(str, (EdsaStringLambda)iterator);
        string_free(str);
      });
    });

    context("on mapping", {
      it("maps a null string", {
        char *str    = NULL;
        char *mapped = string_map(str, (EdsaStringLambda)map);
        assert_that(str is NULL);
        assert_that(mapped is NULL);
      });

      it("maps an empty string", {
        char *str    = string_new("");
        char *mapped = string_map(str, (EdsaStringLambda)map);
        assert_that(str isnot NULL);
        assert_that(mapped isnot NULL);
        assert_that_charptr(str equals to "");
        assert_that_charptr(mapped equals to "");
        string_free(str);
        string_free(mapped);
      });

      it("maps a string", {
        char *str    = string_new("oblivious");
        char *mapped = string_map(str, (EdsaStringLambda)map);
        assert_that(str isnot NULL);
        assert_that(mapped isnot NULL);
        assert_that_charptr(str equals to "oblivious");
        assert_that_charptr(mapped equals to "pcmjwjpvt");
        string_free(str);
        string_free(mapped);
      });
    });
  });
})

#endif
