#ifndef __EDSA_MURMURHASH3_MODULE_SPEC_H_
#define __EDSA_MURMURHASH3_MODULE_SPEC_H_

#include "../../../libs/cSpec/export/cSpec.h"
#include "../../../src/hash/murmurhash3/murmurhash3.h"

module(T_murmurhash3, {
  describe("#murmurhash3", {
    it("hashes small strings", {
      assert_that_size_t(murmurhash3_hash("a", 1) equals to 0x85555565f6597889);
      assert_that_size_t(murmurhash3_hash("ab", 2)
                           equals to 0x938b11ea16ed1b2e);
      assert_that_size_t(murmurhash3_hash("abc", 3)
                           equals to 0xb4963f3f3fad7867);
      assert_that_size_t(murmurhash3_hash("abcd", 4)
                           equals to 0xb87bb7d64656cd4f);
      assert_that_size_t(murmurhash3_hash("abcde", 5)
                           equals to 0x2036d091f496bbb8);
      assert_that_size_t(murmurhash3_hash("abcdef", 6)
                           equals to 0xe47d86bfaca3bf55);
      assert_that_size_t(murmurhash3_hash("abcdefg", 7)
                           equals to 0xa6cd2f9fc09ee499);
      assert_that_size_t(murmurhash3_hash("abcdefgh", 8)
                           equals to 0xcc8a0ab037ef8c02);
    });

    it("hashes medium sized strings", {
      assert_that_size_t(murmurhash3_hash("abcdefghi", 9)
                           equals to 0x0547c0cff13c7964);
      assert_that_size_t(murmurhash3_hash("abcdefghij", 10)
                           equals to 0xb6c15b0d772f8c99);
      assert_that_size_t(murmurhash3_hash("abcdefghijk", 11)
                           equals to 0xa895d0b8df789d02);
      assert_that_size_t(murmurhash3_hash("abcdefghijkl", 12)
                           equals to 0x8ef39bb1e67ae194);
      assert_that_size_t(murmurhash3_hash("abcdefghijklm", 13)
                           equals to 0x1648288da7c0fa73);
      assert_that_size_t(murmurhash3_hash("abcdefghijklmn", 14)
                           equals to 0x91d094a7f5c375e0);
      assert_that_size_t(murmurhash3_hash("abcdefghijklmno", 15)
                           equals to 0x8abe2451890c2ffb);
      assert_that_size_t(murmurhash3_hash("abcdefghijklmnop", 16)
                           equals to 0xc4ca3ca3224cb723);
    });

    it("hashes long strings", {
      assert_that_size_t(murmurhash3_hash("abcdefghijklmnopqrst", 20)
                           equals to 0x310b3726f937e2f1);
      assert_that_size_t(murmurhash3_hash(
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
        "ad minim veniam.",
        148
      ) equals to 0x67e7e82e5eb853a7);
    });
  });
})

#endif
