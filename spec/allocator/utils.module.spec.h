#ifndef __EDSA_ALLOCATOR_UTILS_MODULE_SPEC_H_
#define __EDSA_ALLOCATOR_UTILS_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/utils.h"

module(T_allocator_utils, {
  describe("#allocator_is_power_of_two", {
    it("returns true for powers of two", {
      assert_that(allocator_is_power_of_two(1));
      assert_that(allocator_is_power_of_two(2));
      assert_that(allocator_is_power_of_two(4));
      assert_that(allocator_is_power_of_two(8));
      assert_that(allocator_is_power_of_two(16));
    });

    it("returns false for values that are not powers of two", {
      nassert_that(allocator_is_power_of_two(3));
      nassert_that(allocator_is_power_of_two(5));
      nassert_that(allocator_is_power_of_two(6));
      nassert_that(allocator_is_power_of_two(7));
      nassert_that(allocator_is_power_of_two(9));
    });
  });

  describe("#allocator_align_forward", {
    it("returns the same pointer when it is already aligned", {
      assert_that_size_t(allocator_align_forward(16, 8) equals to 16);
      assert_that_size_t(allocator_align_forward(32, 16) equals to 32);
    });

    it("returns the next aligned pointer when it is unaligned", {
      assert_that_size_t(allocator_align_forward(17, 8) equals to 24);
      assert_that_size_t(allocator_align_forward(33, 16) equals to 48);
    });
  });
})

#endif
