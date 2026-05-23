#include "libs/cSpec/export/cSpec.h"
#include "spec/table/benchmarks/table-general-benchmark.spec.h"

int main(void) {
  cspec_run_suite("all", { T_table_general_benchmark(); });
}
