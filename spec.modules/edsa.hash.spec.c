#include "../libs/cSpec/export/cSpec.h"
#include "../src/preprocessor/preprocessor.h"
#if PREPROCESSOR_32_BIT
  #include "../spec/hash/fnv1a/fnv1a-32.module.spec.h"
  #include "../spec/hash/komihash/komihash-32.module.spec.h"
  #include "../spec/hash/murmurhash3/murmurhash3-32.module.spec.h"
  #include "../spec/hash/xxh3/xxh3-32.module.spec.h"
#else
  #include "../spec/hash/fnv1a/fnv1a.module.spec.h"
  #include "../spec/hash/komihash/komihash.module.spec.h"
  #include "../spec/hash/murmurhash3/murmurhash3.module.spec.h"
  #include "../spec/hash/xxh3/xxh3.module.spec.h"
#endif

int main(void) {
  cspec_run_suite("all", {
    T_fnv1a();
    T_komihash();
    T_murmurhash3();
    T_xxh3();
  });
}
