#include "../libs/cSpec/export/cSpec.h"
#include "../spec/allocator/arena.module.spec.h"
#include "../spec/allocator/pool.module.spec.h"
#include "../spec/allocator/rc.module.spec.h"
#include "../spec/allocator/utils.module.spec.h"

int main(void) {
  cspec_run_suite("all", {
    T_allocator_arena();
    T_allocator_pool();
    T_allocator_rc();
    T_allocator_utils();
  });
}
