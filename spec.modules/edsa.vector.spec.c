#include "../libs/cSpec/export/cSpec.h"
#include "../spec/vector/vector-allocator.module.spec.h"
#include "../spec/vector/vector-base.module.spec.h"
#include "../spec/vector/vector-dup.module.spec.h"
#include "../spec/vector/vector-functional-functions.module.spec.h"
#include "../spec/vector/vector-push-pop-peek.module.spec.h"

int main(void) {
  cspec_run_suite("all", {
    T_vector_base();
    T_vector_allocator();
    T_vector_dup();
    T_vector_functional_functions();
    T_vector_push_pop_peek();
  });
}
