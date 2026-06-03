#ifndef __EDSA_FILE_HANDLER_MODULE_SPEC_H_
#define __EDSA_FILE_HANDLER_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/file-handler/file-handler.h"
#include "../../src/string/string-base.h"

module(T_file_handler, {
  describe("file handler", {
    it("returns NULL when reading a non-existent file", {
      char *res = file_handler_read("this_filename_does_not_exist");
      assert_that(res is NULL);
    });

    it("reads a file after writing to it", {
      file_handler_write("new_file.txt", "hello");
      char *res = file_handler_read("new_file.txt");
      assert_that_charptr(res equals to "hello");
      string_free(res);
    });

    it("writes a line to a file", {
      file_handler_write_line("new_file2.txt", "hello");
      file_handler_write_line("new_file2.txt", "hello2");
      file_handler_write_line("new_file2.txt", "hello3");
      char *res = file_handler_read("new_file2.txt");
      assert_that_charptr(res equals to "hello\nhello2\nhello3\n");
      string_free(res);
    });
  });

  after({ remove("new_file.txt"); });
  after({ remove("new_file2.txt"); });
})

#endif
