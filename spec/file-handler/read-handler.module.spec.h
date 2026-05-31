#ifndef __EDSA_READ_HANDLER_MODULE_SPEC_H_
#define __EDSA_READ_HANDLER_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/file-handler/file-handler.h"
#include "../../src/string/string-base.h"

module(T_read_handler, {
  before({ remove("test.marg"); });

  describe("#reader open", {
    it("loads text character by character", {
      file_handler_write("test.marg", "text");

      char *text = file_handler_read("test.marg");
      assert_that_int(text[0] equals to 't');
      assert_that_int(text[1] equals to 'e');
      assert_that_int(text[2] equals to 'x');
      assert_that_int(text[3] equals to 't');
      assert_that_charptr(text equals to "text");
      string_free(text);
    });
  });

  after({ remove("test.marg"); });
})

#endif
