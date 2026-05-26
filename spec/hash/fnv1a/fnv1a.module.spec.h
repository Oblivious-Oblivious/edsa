#ifndef __EDSA_FNV1A_MODULE_SPEC_H_
#define __EDSA_FNV1A_MODULE_SPEC_H_

#include "../../../libs/cSpec/export/cSpec.h"
#include "../../../src/hash/fnv1a/fnv1a.h"

module(T_fnv1a, {
  describe("#fnv1a", {
    it("hashes small strings", {
      assert_that_size_t(fnv1a_hash("a", 1) equals to 0xaf63dc4c8601ec8c);
      assert_that_size_t(fnv1a_hash("ab", 2) equals to 0x089c4407b545986a);
      assert_that_size_t(fnv1a_hash("abc", 3) equals to 0xe71fa2190541574b);
      assert_that_size_t(fnv1a_hash("abcd", 4) equals to 0xfc179f83ee0724dd);
      assert_that_size_t(fnv1a_hash("abcde", 5) equals to 0x6348c52d762364a8);
      assert_that_size_t(fnv1a_hash("abcdef", 6) equals to 0xd80bda3fbe244a0a);
      assert_that_size_t(fnv1a_hash("abcdefg", 7) equals to 0x406e475017aa7737);
      assert_that_size_t(fnv1a_hash("abcdefgh", 8)
                           equals to 0x25da8c1836a8d66d);
    });

    it("hashes medium sized strings", {
      assert_that_size_t(fnv1a_hash("abcdefghi", 9)
                           equals to 0xfb321124e0e3a8cc);
      assert_that_size_t(fnv1a_hash("abcdefghij", 10)
                           equals to 0xb9bbc7aa22d79212);
      assert_that_size_t(fnv1a_hash("abcdefghijk", 11)
                           equals to 0x71a6bf19344de39b);
      assert_that_size_t(fnv1a_hash("abcdefghijkl", 12)
                           equals to 0x6c3aaed3e05a5cb5);
      assert_that_size_t(fnv1a_hash("abcdefghijklm", 13)
                           equals to 0x4213ea06398bc308);
      assert_that_size_t(fnv1a_hash("abcdefghijklmn", 14)
                           equals to 0xd39a0e93c87d0652);
      assert_that_size_t(fnv1a_hash("abcdefghijklmno", 15)
                           equals to 0x0bcd021dac7199a7);
      assert_that_size_t(fnv1a_hash("abcdefghijklmnop", 16)
                           equals to 0x7ef46f6c05086855);
    });

    it("hashes long strings", {
      assert_that_size_t(fnv1a_hash("abcdefghijklmnopqrst", 20)
                           equals to 0x540532bba32d3e4d);
      assert_that_size_t(fnv1a_hash(
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
        "ad minim veniam.",
        148
      ) equals to 0x02c6ace0b1c25dca);
    });
  });
})

#endif
