#ifndef __EDSA_PREPROCESSOR_VERSION_MODULE_SPEC_H_
#define __EDSA_PREPROCESSOR_VERSION_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/preprocessor/preprocessor.h"

module(T_preprocessor_version, {
  it("returns the current version", {
    assert_that_int(PREPROCESSOR_C_VERSION equals to 2023);
  });
})

#endif
