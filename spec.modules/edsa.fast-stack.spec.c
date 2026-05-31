#include "../libs/cSpec/export/cSpec.h"
#include "../spec/fast-stack/fast-stack.module.spec.h"

int main(void) {
  cspec_run_suite("all", { T_fast_stack(); });
}
