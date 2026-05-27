#ifndef __EDSA_HASH_FNV1A_32_MODULE_SPEC_H_
#define __EDSA_HASH_FNV1A_32_MODULE_SPEC_H_

#include "../../../libs/cSpec/export/cSpec.h"
#include "../../../src/hash/fnv1a/fnv1a.h"

module(T_fnv1a, {
  describe("#fnv1a 32-bit", {
    it("hashes small strings", {
      assert_that_size_t(hash_fnv1a("a", 1) equals to 0xe40c292c);
      assert_that_size_t(hash_fnv1a("ab", 2) equals to 0x4d2505ca);
      assert_that_size_t(hash_fnv1a("abc", 3) equals to 0x1a47e90b);
      assert_that_size_t(hash_fnv1a("abcd", 4) equals to 0xce3479bd);
      assert_that_size_t(hash_fnv1a("abcde", 5) equals to 0x749bcf08);
      assert_that_size_t(hash_fnv1a("abcdef", 6) equals to 0xff478a2a);
      assert_that_size_t(hash_fnv1a("abcdefg", 7) equals to 0x2a9eb737);
      assert_that_size_t(hash_fnv1a("abcdefgh", 8) equals to 0x76daaa8d);
    });

    it("hashes medium sized strings", {
      assert_that_size_t(hash_fnv1a("abcdefghi", 9) equals to 0xfe3b04ec);
      assert_that_size_t(hash_fnv1a("abcdefghij", 10) equals to 0xbce81ef2);
      assert_that_size_t(hash_fnv1a("abcdefghijk", 11) equals to 0xfa682adb);
      assert_that_size_t(hash_fnv1a("abcdefghijkl", 12) equals to 0xe8fb3e15);
      assert_that_size_t(hash_fnv1a("abcdefghijklm", 13) equals to 0x3b8356e8);
      assert_that_size_t(hash_fnv1a("abcdefghijklmn", 14) equals to 0x35c134f2);
      assert_that_size_t(hash_fnv1a("abcdefghijklmno", 15)
                           equals to 0x3c25d327);
      assert_that_size_t(hash_fnv1a("abcdefghijklmnop", 16)
                           equals to 0x068bb1f5);
    });

    it("hashes long strings", {
      assert_that_size_t(hash_fnv1a("abcdefghijklmnopqrst", 20)
                           equals to 0xd0cc2b2d);
      assert_that_size_t(hash_fnv1a(
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
        "ad minim veniam.",
        148
      ) equals to 0xe71876aa);
    });
  });
})

#endif
