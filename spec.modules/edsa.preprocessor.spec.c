#include "../libs/cSpec/export/cSpec.h"
#include "../spec/preprocessor/preprocessor-number-of-elements.module.spec.h"
#include "../spec/preprocessor/preprocessor-version.module.spec.h"

int main(void) {
  cspec_run_suite("all", {
    T_preprocessor_number_of_elements();
    T_preprocessor_version();
  });
}
