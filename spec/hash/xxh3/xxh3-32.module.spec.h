#ifndef __EDSA_XXH3_32_MODULE_SPEC_H_
#define __EDSA_XXH3_32_MODULE_SPEC_H_

#include "../../../libs/cSpec/export/cSpec.h"
#include "../../../src/hash/xxh3/xxh3.h"

module(T_xxh3, {
  describe("#xxh3 32-bit", {
    it("hashes small strings", {
      assert_that_size_t(hash_xxh3("a", 1) equals to 0x550d7456);
      assert_that_size_t(hash_xxh3("ab", 2) equals to 0x4999fc53);
      assert_that_size_t(hash_xxh3("abc", 3) equals to 0x32d153ff);
      assert_that_size_t(hash_xxh3("abcd", 4) equals to 0xa3643705);
      assert_that_size_t(hash_xxh3("abcde", 5) equals to 0x9738f19b);
      assert_that_size_t(hash_xxh3("abcdef", 6) equals to 0x8b7cd587);
      assert_that_size_t(hash_xxh3("abcdefg", 7) equals to 0x9dd093b3);
      assert_that_size_t(hash_xxh3("abcdefgh", 8) equals to 0x0bb3c6bb);
    });

    it("hashes medium sized strings", {
      assert_that_size_t(hash_xxh3("abcdefghi", 9) equals to 0xd03c13fd);
      assert_that_size_t(hash_xxh3("abcdefghij", 10) equals to 0x8b988cfe);
      assert_that_size_t(hash_xxh3("abcdefghijk", 11) equals to 0x9db8a215);
      assert_that_size_t(hash_xxh3("abcdefghijkl", 12) equals to 0xed035ab5);
      assert_that_size_t(hash_xxh3("abcdefghijklm", 13) equals to 0xa5b14016);
      assert_that_size_t(hash_xxh3("abcdefghijklmn", 14) equals to 0x684d3123);
      assert_that_size_t(hash_xxh3("abcdefghijklmno", 15) equals to 0xb918a375);
      assert_that_size_t(hash_xxh3("abcdefghijklmnop", 16)
                           equals to 0x9d2d8b62);
    });

    it("hashes long strings", {
      assert_that_size_t(hash_xxh3("abcdefghijklmnopqrst", 20)
                           equals to 0x91618150);
      assert_that_size_t(hash_xxh3(
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
        "ad minim veniam.",
        148
      ) equals to 0x8445ab05);
    });
  });
})

#endif
