#ifndef __EDSA_ALLOCATOR_RC_MODULE_SPEC_H_
#define __EDSA_ALLOCATOR_RC_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/rc.h"
#include "../../src/string/string-base.h"

static void allocator_rc_string_free(void *obj) {
  char *value = (char *)obj;
  string_free(value);
}

module(T_allocator_rc, {
  it("performs an end to end reference counted object test", {
    AllocatorRc counted;
    char *test = string_new("test");

    allocator_rc_alloc(&counted, allocator_rc_string_free);
    allocator_rc_use(&counted);

    assert_that_charptr(test equals to "test");
    assert_that_int(counted.count equals to 1);

    allocator_rc_release(test, &counted);
  });

  it("keeps a shared object alive until the last owner releases it", {
    AllocatorRc counted;
    char *test = string_new("shared");

    allocator_rc_alloc(&counted, allocator_rc_string_free);
    allocator_rc_use(&counted);
    allocator_rc_use(&counted);
    allocator_rc_use(&counted);
    assert_that_int(counted.count equals to 3);

    allocator_rc_release(test, &counted);
    assert_that(test isnot NULL);
    assert_that_int(counted.count equals to 2);
    assert_that_charptr(test equals to "shared");

    allocator_rc_release(test, &counted);
    assert_that(test isnot NULL);
    assert_that_int(counted.count equals to 1);

    allocator_rc_release(test, &counted);
    assert_that(test is NULL);
  });
})

#endif
