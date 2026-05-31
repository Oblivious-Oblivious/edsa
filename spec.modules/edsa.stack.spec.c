#include "../libs/cSpec/export/cSpec.h"
#include "../spec/stack/stack.module.spec.h"

int main(void) {
  cspec_run_suite("all", { T_stack(); });
}
