#ifndef __EDSA_BOOLEAN_MODULE_SPEC_H_
#define __EDSA_BOOLEAN_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/boolean/boolean.h"

module(T_boolean, {
  describe("boolean", {
    it("returns true", {
      bool v = true;
      assert_that(v is true);
    });

    it("returns false", {
      bool v = false;
      assert_that(v is false);
    });
  });
})

#endif
