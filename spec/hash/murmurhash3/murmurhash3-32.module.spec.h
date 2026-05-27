#ifndef __EDSA_HASH_MURMURHASH3_32_MODULE_SPEC_H_
#define __EDSA_HASH_MURMURHASH3_32_MODULE_SPEC_H_

#include "../../../libs/cSpec/export/cSpec.h"
#include "../../../src/hash/murmurhash3/murmurhash3.h"

module(T_murmurhash3, {
  describe("#murmurhash3 32-bit", {
    it("hashes small strings", {
      assert_that_size_t(hash_murmurhash3("a", 1) equals to 0xa794933c);
      assert_that_size_t(hash_murmurhash3("ab", 2) equals to 0x158451df);
      assert_that_size_t(hash_murmurhash3("abc", 3) equals to 0x75cdc6d1);
      assert_that_size_t(hash_murmurhash3("abcd", 4) equals to 0x96b6ccaa);
      assert_that_size_t(hash_murmurhash3("abcde", 5) equals to 0xc5402efb);
      assert_that_size_t(hash_murmurhash3("abcdef", 6) equals to 0xe17cb90a);
      assert_that_size_t(hash_murmurhash3("abcdefg", 7) equals to 0x90b541d9);
      assert_that_size_t(hash_murmurhash3("abcdefgh", 8) equals to 0xaef41136);
    });

    it("hashes medium sized strings", {
      assert_that_size_t(hash_murmurhash3("abcdefghi", 9) equals to 0xad058c1c);
      assert_that_size_t(hash_murmurhash3("abcdefghij", 10)
                           equals to 0xf5d92ea7);
      assert_that_size_t(hash_murmurhash3("abcdefghijk", 11)
                           equals to 0xa0c8c9dd);
      assert_that_size_t(hash_murmurhash3("abcdefghijkl", 12)
                           equals to 0x738503fe);
      assert_that_size_t(hash_murmurhash3("abcdefghijklm", 13)
                           equals to 0xc13aa215);
      assert_that_size_t(hash_murmurhash3("abcdefghijklmn", 14)
                           equals to 0x75ec118e);
      assert_that_size_t(hash_murmurhash3("abcdefghijklmno", 15)
                           equals to 0xee6d1d69);
      assert_that_size_t(hash_murmurhash3("abcdefghijklmnop", 16)
                           equals to 0x9fd27627);
    });

    it("hashes long strings", {
      assert_that_size_t(hash_murmurhash3("abcdefghijklmnopqrst", 20)
                           equals to 0x46253419);
      assert_that_size_t(hash_murmurhash3(
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
        "ad minim veniam.",
        148
      ) equals to 0x5b95334d);
    });
  });
})

#endif
