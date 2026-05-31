#include "../libs/cSpec/export/cSpec.h"
#include "../spec/linked-list/linked-list-base.module.spec.h"
#include "../spec/linked-list/linked-list-dup.module.spec.h"
#include "../spec/linked-list/linked-list-functional-functions.module.spec.h"

int main(void) {
  cspec_run_suite("all", {
    T_linked_list_base();
    T_linked_list_dup();
    T_linked_list_functional_functions();
  });
}
