#include "../libs/cSpec/export/cSpec.h"
#include "../spec/file-handler/file-handler.module.spec.h"
#include "../spec/file-handler/read-handler.module.spec.h"
#include "../spec/file-handler/write-handler.module.spec.h"

int main(void) {
  cspec_run_suite("all", {
    T_file_handler();
    T_read_handler();
    T_write_handler();
  });
}
