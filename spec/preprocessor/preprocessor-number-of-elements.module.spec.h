#ifndef __EDSA_PREPROCESSOR_NUMBER_OF_ELEMENTS_MODULE_SPEC_H_
#define __EDSA_PREPROCESSOR_NUMBER_OF_ELEMENTS_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/preprocessor/preprocessor.h"

module(T_preprocessor_number_of_elements, {
  describe("#PREPROCESSOR_NUMBER_OF_ELEMENTS", {
    it("counts for 1 element", {
      assert_that_int(PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(1)
                        equals to 1);
    });

    it("counts for 2 elements", {
      assert_that_int(PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(1, 2)
                        equals to 2);
    });

    it("counts for 3 elements", {
      assert_that_int(PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(1, 2, 3)
                        equals to 3);
    });

    it("counts for 42 elements", {
      assert_that_int(PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
        20,
        21,
        22,
        23,
        24,
        25,
        26,
        27,
        28,
        29,
        30,
        31,
        32,
        33,
        34,
        35,
        36,
        37,
        38,
        39,
        40,
        41,
        42
      ) equals to 42);
    });
  });
})

#endif
