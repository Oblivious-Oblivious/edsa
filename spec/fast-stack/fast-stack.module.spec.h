#ifndef __EDSA_FAST_STACK_MODULE_SPEC_H_
#define __EDSA_FAST_STACK_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/fast-stack/fast-stack.h"

module(T_fast_stack, {
  int st[65536];
  int *sp = st;

  it("is empty after 1 push and 1 pop", {
    fs_push(sp, 42);
    int res = fs_pop(sp);
    assert_that(res is 42);
  });

  it("is not empty after 2 pushes and 1 pop", {
    fs_push(sp, 42);
    fs_push(sp, 43);
    int res = fs_pop(sp);
    assert_that(res is 43);
  });

  it("pops `x` after pushing `x`", {
    fs_push(sp, 99);
    assert_that_int(fs_pop(sp) equals to 99);
    fs_push(sp, 88);
    assert_that_int(fs_pop(sp) equals to 88);
  });

  it("pops `y` then `x` after pushing `x` then `y`", {
    fs_push(sp, 99);
    fs_push(sp, 88);
    assert_that_int(fs_pop(sp) equals to 88);
    assert_that_int(fs_pop(sp) equals to 99);
  });
})

#endif
