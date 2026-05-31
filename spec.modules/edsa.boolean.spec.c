#include "../libs/cSpec/export/cSpec.h"
#include "../spec/boolean/boolean.module.spec.h"

int main(void) {
  cspec_run_suite("all", { T_boolean(); });
}
