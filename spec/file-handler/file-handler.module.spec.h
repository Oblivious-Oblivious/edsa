#ifndef __EDSA_FILE_HANDLER_MODULE_SPEC_H_
#define __EDSA_FILE_HANDLER_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/file-handler/file-handler.h"

static EdsaFileHandler loader = {0};
static void setup_file_loader(void) { file_handler_init(&loader); }

module(T_file_handler, {
  before_each(&setup_file_loader);

  describe("File Loader", {
    it("creates a file_loader object", {
      EdsaFileHandler fl = {0};
      file_handler_init(&fl);
      assert_that(&fl isnot NULL);
      assert_that(fl.fd is NULL);
      assert_that(fl.filepath is NULL);
    });

    context("on opening an existing file", {
      bool _res = file_handler_open(&loader, "new_file.txt", "w");
      assert_that(_res is true);

      it("reads file: `new_file.txt`", {
        int actual = file_handler_open(&loader, "new_file.txt", "r");
        assert_that(actual is true);
      });

      file_handler_close(&loader);
    });

    context("on opening an non existent file", {
      it("fails to read a file that is not yet created", {
        int actual =
          file_handler_open(&loader, "this_filename_does_not_exist", "r");
        assert_that(actual is false);
      });
    });

    context("on closing a file loader", {
      it("opens a file and successfully closes the buffer", {
        bool _res = file_handler_open(&loader, "new_file.txt", "r");
        assert_that(_res is true);
        file_handler_close(&loader);
        assert_that(loader.fd isnot NULL);
      });
    });

    context("on deiniting a file loader", {
      it("de inits the file", {
        bool _res = file_handler_open(&loader, "new_file.txt", "r");
        assert_that(_res is true);
        file_handler_deinit(&loader);
        assert_that(loader.fd is NULL);
        assert_that(loader.filepath is NULL);
      });
    });
  });

  after({
    remove("new_file.txt");
    remove("test_file.txt");
  });
})

#endif
