#ifndef __EDSA_STRING_BASE_MODULE_SPEC_H_
#define __EDSA_STRING_BASE_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/string/string-base.h"
#include "../../src/string/string-editing.h"

static void _external_string_add(char **str, const char *value) {
  string_add(*str, value);
}

static void _external_vector_add_string2(char ***v, const char *value) {
  vector_add(*v, (char *)value);
}

static void _external_vector_add_string(char ***v, char *value) {
  char *copy = string_new(value);
  string_add(copy, "sth else");
  _external_vector_add_string2(v, copy);
}

static void _external_vector_add_int(int **v, int value) {
  vector_add(*v, value);
}

module(T_string_base, {
  describe("string", {
    it("initializes a null string", {
      char *str = NULL;
      assert_that(str is NULL);
      string_add(str, "test");
      assert_that(str isnot NULL);
      assert_that_charptr(str equals to "test");
      string_free(str);
    });

    context("on initializing a string", {
      it("creates a new empty string", {
        char *str = string_new("");
        assert_that(str isnot NULL);
        char *str2 = string_new("");
        assert_that(string_equals(str, str2));
        string_free(str);
        string_free(str2);
      });

      it("creates a new non-empty string", {
        char *str = string_new("anything");
        assert_that(str isnot NULL);
        char *str2 = string_new("anything");
        assert_that(string_equals(str, str2));
        string_free(str);
        string_free(str2);
      });

      it("creates a new string exactly 1 char long", {
        char *str = string_new("a");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "a");
        string_free(str);
      });

      it("creates a new string exactly 2 chars long", {
        char *str = string_new("ab");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "ab");
        string_free(str);
      });

      it("creates a new string exactly 4 chars long", {
        char *str = string_new("1234");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "1234");
        string_free(str);
      });

      it("creates a new string exactly 8 chars long", {
        char *str = string_new("12345678");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "12345678");
        string_free(str);
      });

      it("creates a new string exactly 15 chars long", {
        char *str = string_new("123456789012345");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "123456789012345");
        string_free(str);
      });

      it("creates a new string exactly 16 chars long", {
        char *str = string_new("1234567890123456");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "1234567890123456");
        string_free(str);
      });

      it("creates a new string exactly 17 chars long", {
        char *str = string_new("12345678901234567");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "12345678901234567");
        string_free(str);
      });

      it("creates a new string exactly 32 chars long", {
        char *str = string_new("1234567890123456789012345678901234567890");
        assert_that(str isnot NULL);
        assert_that_charptr(
          str equals to "1234567890123456789012345678901234567890"
        );
        string_free(str);
      });
    });

    context("on adding strings to a string", {
      it("adds a null string to a null string", {
        char *str = NULL;
        string_add(str, NULL);
        assert_that(str is NULL);
        string_free(str);
      });

      it("adds a null string to a valid string", {
        char *str = string_new("test");
        string_add(str, NULL);
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "test");
        string_free(str);
      });

      it("adds a valid string to a null string", {
        char *str = NULL;
        string_add(str, "test");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "test");
        string_free(str);
      });

      it("adds a string to a string", {
        char *str        = NULL;
        char *str2       = string_new("test2");
        const char *str3 = "test3";
        string_add(str, str2);
        assert_that_charptr(str equals to "test2");
        assert_that_charptr(str2 equals to "test2");
        string_add(str, str3);
        assert_that_charptr(str equals to "test2test3");
        assert_that_charptr(str2 equals to "test2");
        assert_that_charptr(str3 equals to "test3");
        string_free(str);
        string_free(str2);
      });

      it("adds an initialized string to a another string", {
        char *str           = NULL;
        char *str2          = string_new("test2");
        const char *str3    = string_new("test3");
        char *nonconst_str3 = (char *)str3;

        string_addi(str, str2);
        assert_that_charptr(str equals to "test2");
        assert_that_charptr(str2 equals to "test2");

        string_addi(str, str3);
        assert_that_charptr(str equals to "test2test3");
        assert_that_charptr(str2 equals to "test2");
        assert_that_charptr(str3 equals to "test3");

        string_free(str);
        string_free(str2);
        string_free(nonconst_str3);
      });

      it("adds a string to a string with a format", {
        char *str        = NULL;
        char *str2       = string_new("test2");
        const char *str3 = "test3";
        string_addf(&str, "%s%s", str2, str3, "ignored");
        assert_that_charptr(str equals to "test2test3");
        assert_that_charptr(str2 equals to "test2");
        assert_that_charptr(str3 equals to "test3");
        string_addf(&str, "%s", "somethingelse");
        assert_that_charptr(str equals to "test2test3somethingelse");
        string_free(str);
        string_free(str2);
      });

      it("adds a string with a cutoff of a given length", {
        char *str        = NULL;
        char *str2       = string_new("test2");
        const char *str3 = "test3";
        string_addn(str, str2, 2);
        assert_that_charptr(str equals to "te");
        assert_that_charptr(str2 equals to "test2");
        string_addn(str, str3, 3);
        assert_that_charptr(str equals to "tetes");
        assert_that_charptr(str2 equals to "test2");
        assert_that_charptr(str3 equals to "test3");
        string_free(str);
        string_free(str2);
      });
    });

    context("on adding literals to a string", {
      it("adds a simple character to a string", {
        char *str = NULL;
        string_addf(&str, "%c", 'a');
        assert_that_charptr(str equals to "a");
        string_addf(&str, "%c", 'b');
        assert_that_charptr(str equals to "ab");
        string_addf(&str, "%c", 'c');
        assert_that_charptr(str equals to "abc");
        string_free(str);
      });
    });

    context("when adding characters to a string it remains null terminated", {
      it("adds a simple character to a string", {
        char *input = string_new("$var!+(@another?)");
        char *token = string_substring(input, 0, 4);
        string_skip_first(input, 4);
        assert_that_charptr(token equals to "$var");
        assert_that_int(string_size(token) equals to 4);
        string_addf(&token, "%c", input[0]);
        string_skip_first(input, 1);
        assert_that_charptr(token equals to "$var!");
        assert_that_int(string_size(token) equals to 5);
        assert_that_int(string_size(input) equals to 12);
        assert_that_charptr(input equals to "+(@another?)");
        string_free(token);
        string_free(input);
      });
    });

    context("on a string pointer is not NULL", {
      it("returns the char* when calling `string_get`", {
        char *str = string_new("initial");
        assert_that(sizeof(str) is sizeof(char *));
        string_free(str);
      });
    });

    context("on the initial value exists", {
      it("returns the correct char* when calling `string_get`", {
        char *str = string_new("initial");
        assert_that_charptr(str equals to "initial");
        string_free(str);
      });
    });

    context("on #shorten/#skip/#ignore", {
      it("shortens a string to a given length", {
        char *str = string_new("this is a test");
        string_shorten(str, string_size(str) - 5);
        assert_that_charptr(str equals to "this is a");
        string_free(str);
      });

      it("shortens a string to a length shorter than the string size", {
        char *str = string_new("this is a test");
        string_shorten(str, string_size(str) - 42);
        assert_that_charptr(str equals to "");
        string_free(str);
      });

      it("shortens a string to a length greater than the string size", {
        char *str = string_new("this is a test");
        string_shorten(str, string_size(str) + 42);
        assert_that_charptr(str equals to "this is a test");
        string_free(str);
      });

      it("skips first string characters by a given length", {
        char *str = string_new("this is a test");
        string_skip_first(str, 5);
        assert_that_charptr(str equals to "is a test");
        string_free(str);
      });

      it("skips first string characters by a length greater than string size", {
        char *str = string_new("this is a test");
        string_skip_first(str, 42);
        assert_that_charptr(str equals to "");
        string_free(str);
      });

      it("skips first string characters by a length shorter than string size", {
        char *str = string_new("this is a test");
        string_skip_first(str, -42);
        assert_that_charptr(str equals to "this is a test");
        string_free(str);
      });

      it("ignores last string characters by a given length", {
        char *str = string_new("this is a test");
        string_ignore_last(str, 5);
        assert_that_charptr(str equals to "this is a");
        string_free(str);
      });

      it("ignores last string chars by a length greater than string size", {
        char *str = string_new("this is a test");
        string_ignore_last(str, 42);
        assert_that_charptr(str equals to "");
        string_free(str);
      });

      it("ignores last string chars by a length shorter than string size", {
        char *str = string_new("this is a test");
        string_ignore_last(str, -42);
        assert_that_charptr(str equals to "this is a test");
        string_free(str);
      });
    });

    it("clears a string", {
      char *str = string_new("this is a test");
      string_delete(str);
      assert_that_charptr(str equals to "");
      string_free(str);
    });

    it("finds the size of a string", {
      char *str = string_new("this is a test");
      assert_that_int(string_size(str) equals to 14);
      string_free(str);
    });

    it("tests equality between strings", {
      char *one = string_new("test");
      char *two = string_new("test");
      assert_that(string_equals(one, two));

      char *three = string_new("test");
      string_add(three, "sth else");
      nassert_that(string_equals(one, three));

      string_free(one);
      string_free(two);
      string_free(three);
    });

    context("#string_remove_underscores", {
      it("removes underscores from strings", {
        char *test = string_new("a_word_with_underscores");
        string_remove_underscores(test);
        assert_that_charptr(test equals to "awordwithunderscores");
        string_free(test);

        test = string_new("42_000_000");
        string_remove_underscores(test);
        assert_that_charptr(test equals to "42000000");

        string_free(test);
      });

      it("returns the same string if it doesn't contain underscores", {
        char *test = string_new("42");
        string_remove_underscores(test);
        assert_that_charptr(test equals to "42");
        string_free(test);
      });
    });

    context("on external function string manipulation", {
      it("adds a string that has been initialized", {
        char *test = string_new("initial");
        _external_string_add(&test, " - test");
        assert_that_charptr(test equals to "initial - test");
        string_free(test);
      });

      it("adds a string that has NOT been initialized", {
        char *test = string_new("");
        _external_string_add(&test, "this is an initial string");
        assert_that_charptr(test equals to "this is an initial string");
        string_free(test);
      });

      it("adds a string in a vector of strings in an extenral function", {
        char **v = vector_new("one");
        assert_that(vector_size(v) is 1);
        assert_that_charptr(v[0] equals to "one");
        char *two   = string_new("two");
        char *three = string_new("three");
        _external_vector_add_string(&v, two);
        _external_vector_add_string(&v, three);
        assert_that_int(vector_size(v) equals to 3);
        assert_that_charptr(v[1] equals to "twosth else");
        assert_that_charptr(v[2] equals to "threesth else");
        string_free(v[1]);
        string_free(v[2]);
        string_free(two);
        string_free(three);
        vector_free(v);
      });

      it("adds numbers in a vector of numbers in an extenral function", {
        int *v = NULL;
        assert_that(vector_size(v) is 0);
        for(int i = 0; i < 20; i++) {
          _external_vector_add_int(&v, i);
        }

        for(int i = 0; i < 20; i++) {
          assert_that_int(v[i] equals to i);
        }

        assert_that_int(vector_size(v) equals to 20);

        vector_free(v);
      });
    });

    it("frees the memory of a string", {
      char *str = string_new("this is a test");
      assert_that(str isnot NULL);
      string_free(str);
      assert_that(str is NULL);
    });
  });
})

#endif
