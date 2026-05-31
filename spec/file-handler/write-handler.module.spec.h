#ifndef __EDSA_WRITE_HANDLER_MODULE_SPEC_H_
#define __EDSA_WRITE_HANDLER_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/file-handler/file-handler.h"
#include "../../src/string/string-base.h"

module(T_write_handler, {
  describe("#write", {
    it("writes `test data` to input file named `test_write.txt`", {
      file_handler_write("test_write.txt", "test data");
      char *res = file_handler_read("test_write.txt");
      assert_that_charptr(res equals to "test data");
      string_free(res);
    });
  });

  describe("#write line", {
    it("writes `test data` to file `test_write_line.txt` with a newline", {
      file_handler_write_line("test_write_line.txt", "test data");
      char *res = file_handler_read("test_write_line.txt");
      assert_that_charptr(res equals to "test data\n");
      string_free(res);
    });
  });

  after({
    remove("test_write.txt");
    remove("test_write_line.txt");
  });
})

#endif
