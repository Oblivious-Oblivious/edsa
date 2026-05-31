#include "../libs/cSpec/export/cSpec.h"
#include "../spec/min-pq-binary-heap/min-pq-binary-heap.module.spec.h"

int main(void) {
  cspec_run_suite("all", { T_min_pq_binary_heap_base(); });
}
