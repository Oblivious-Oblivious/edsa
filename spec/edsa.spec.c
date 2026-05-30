#include "../libs/cSpec/export/cSpec.h"
#include "../src/preprocessor/preprocessor.h"
#include "allocator/arena.module.spec.h"
#include "boolean/boolean.module.spec.h"
#include "fast-stack/fast-stack.module.spec.h"
#include "file-handler/file-handler.module.spec.h"
#include "file-handler/read-handler.module.spec.h"
#include "file-handler/write-handler.module.spec.h"
#if PREPROCESSOR_32_BIT
  #include "hash/fnv1a/fnv1a-32.module.spec.h"
  #include "hash/komihash/komihash-32.module.spec.h"
  #include "hash/murmurhash3/murmurhash3-32.module.spec.h"
  #include "hash/xxh3/xxh3-32.module.spec.h"
#else
  #include "hash/fnv1a/fnv1a.module.spec.h"
  #include "hash/komihash/komihash.module.spec.h"
  #include "hash/murmurhash3/murmurhash3.module.spec.h"
  #include "hash/xxh3/xxh3.module.spec.h"
#endif
#include "linked-list/linked-list-base.module.spec.h"
#include "linked-list/linked-list-dup.module.spec.h"
#include "linked-list/linked-list-functional-functions.module.spec.h"
#include "min-pq-binary-heap/min-pq-binary-heap.module.spec.h"
#include "preprocessor/preprocessor-number-of-elements.module.spec.h"
#include "preprocessor/preprocessor-version.module.spec.h"
#include "stack/stack.module.spec.h"
#include "string/string-base.module.spec.h"
#include "string/string-dup.module.spec.h"
#include "string/string-functional.module.spec.h"
#include "string/string-interpolation.module.spec.h"
#include "string/string-split.module.spec.h"
#include "string/string-substring.module.spec.h"
#include "table/benchmarks/table-general-benchmark.spec.h"
#include "table/table.module.spec.h"
#include "vector/vector-base.module.spec.h"
#include "vector/vector-dup.module.spec.h"
#include "vector/vector-functional-functions.module.spec.h"
#include "vector/vector-push-pop-peek.module.spec.h"

int main(void) {
  cspec_run_suite("all", {
    T_allocator_arena();

    T_boolean();

    T_fast_stack();

    T_file_handler();
    T_read_handler();
    T_write_handler();

    T_fnv1a();
    T_komihash();
    T_murmurhash3();
    T_xxh3();

    T_linked_list_base();
    T_linked_list_dup();
    T_linked_list_functional_functions();

    T_min_pq_binary_heap_base();

    T_preprocessor_number_of_elements();
    T_preprocessor_version();

    T_stack();

    T_string_base();
    T_string_dup();
    T_string_functional();
    T_string_interpolation();
    T_string_split();
    T_string_substring();

    T_table_general_benchmark();
    T_table();

    T_vector_base();
    T_vector_dup();
    T_vector_functional_functions();
    T_vector_push_pop_peek();
  });
}
