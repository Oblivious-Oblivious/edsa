#ifndef __EDSA_STRING_SPLIT_MODULE_SPEC_H_
#define __EDSA_STRING_SPLIT_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/string/string-base.h"
#include "../../src/string/string-editing.h"

module(T_string_split, {
  describe("string split", {
    context("on invalid/NULL delimeter", {
      it("splits a null string", {
        char *str   = NULL;
        char **list = string_split(str, '\0');
        assert_that(str is NULL);
        assert_that(list is NULL);
      });

      it("splits an empty string string", {
        char *str   = string_new("");
        char **list = string_split(str, '\0');
        assert_that(str isnot NULL);
        assert_that(list isnot NULL);
        assert_that_int(vector_size(list) equals to 1);
        assert_that_charptr(list[0] equals to "");
        string_free(str);
        string_free(list[0]);
        vector_free(list);
      });

      it("splits a normal string", {
        char *str   = string_new("oblivious");
        char **list = string_split(str, '\0');
        assert_that(str isnot NULL);
        assert_that(list isnot NULL);
        assert_that_int(vector_size(list) equals to 1);
        assert_that_charptr(list[0] equals to "oblivious");
        string_free(str);
        string_free(list[0]);
        vector_free(list);
      });
    });

    context("on valid delimeter", {
      it("splits a null string", {
        char *str   = NULL;
        char **list = string_split(str, ',');
        assert_that(str is NULL);
        assert_that(list is NULL);
      });

      it("splits a normal string with an empty delimeter", {
        char *str   = string_new("oblivious");
        char **list = string_split(str, '\0');
        assert_that(str isnot NULL);
        assert_that(list isnot NULL);
        assert_that_charptr(str equals to "oblivious");
        assert_that(vector_size(list) is 1);
        assert_that_charptr(list[0] equals to "oblivious");
        string_free(str);
        string_free(list[0]);
        vector_free(list);
      });

      it("splits a string with a delimeter", {
        char *str   = string_new("oblivious");
        char **list = string_split(str, 'l');
        assert_that(str isnot NULL);
        assert_that(list isnot NULL);
        assert_that_charptr(str equals to "oblivious");
        assert_that(vector_size(list) is 2);
        assert_that_charptr(list[0] equals to "ob");
        assert_that_charptr(list[1] equals to "ivious");
        string_free(str);
        string_free(list[0]);
        string_free(list[1]);
        vector_free(list);
      });

      it("splits a string with multiple commas", {
        char *str   = string_new("1,2,3,4,5,6,7");
        char **list = string_split(str, ',');
        assert_that(str isnot NULL);
        assert_that(list isnot NULL);
        assert_that(vector_size(list) is 7);
        assert_that_charptr(list[0] equals to "1");
        assert_that_charptr(list[1] equals to "2");
        assert_that_charptr(list[2] equals to "3");
        assert_that_charptr(list[3] equals to "4");
        assert_that_charptr(list[4] equals to "5");
        assert_that_charptr(list[5] equals to "6");
        assert_that_charptr(list[6] equals to "7");
        string_free(str);
        string_free(list[0]);
        string_free(list[1]);
        string_free(list[2]);
        string_free(list[3]);
        string_free(list[4]);
        string_free(list[5]);
        string_free(list[6]);
        vector_free(list);
      });

      it("splits a string that is the same as the delimeter", {
        char *str   = string_new("o");
        char **list = string_split(str, 'o');
        assert_that(list isnot NULL);
        assert_that(vector_size(list) is 2);
        assert_that_charptr(list[0] equals to "");
        assert_that_charptr(list[1] equals to "");
        string_free(str);
        string_free(list[0]);
        string_free(list[1]);
        vector_free(list);
      });

      it("splits a multi line string with newlines", {
        char *str   = string_new("(\"multi\nline\nstring\" puts)");
        char **list = string_split(str, '\n');
        assert_that(list isnot NULL);
        assert_that_size_t(vector_size(list) equals to 3);
        assert_that_charptr(list[0] equals to "(\"multi");
        assert_that_charptr(list[1] equals to "line");
        assert_that_charptr(list[2] equals to "string\" puts)");
        string_free(str);
        string_free(list[0]);
        string_free(list[1]);
        string_free(list[2]);
        vector_free(list);
      });
    });
  });
})

#endif
