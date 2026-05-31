#include "../libs/cSpec/export/cSpec.h"
#include "../spec/string/string-base.module.spec.h"
#include "../spec/string/string-dup.module.spec.h"
#include "../spec/string/string-functional.module.spec.h"
#include "../spec/string/string-interpolation.module.spec.h"
#include "../spec/string/string-split.module.spec.h"
#include "../spec/string/string-substring.module.spec.h"

int main(void) {
  cspec_run_suite("all", {
    T_string_base();
    T_string_dup();
    T_string_functional();
    T_string_interpolation();
    T_string_split();
    T_string_substring();
  });
}
