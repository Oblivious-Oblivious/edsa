#ifndef __EDSA_KOMIHASH_32_MODULE_SPEC_H_
#define __EDSA_KOMIHASH_32_MODULE_SPEC_H_

#include "../../../libs/cSpec/export/cSpec.h"
#include "../../../src/hash/komihash/komihash.h"

module(T_komihash, {
  describe("#komihash 32-bit", {
    it("hashes small strings", {
      assert_that_size_t(komihash_hash("a", 1) equals to 0xf8e133e3);
      assert_that_size_t(komihash_hash("ab", 2) equals to 0xcbe38e68);
      assert_that_size_t(komihash_hash("abc", 3) equals to 0xbb74a844);
      assert_that_size_t(komihash_hash("abcd", 4) equals to 0x074193d4);
      assert_that_size_t(komihash_hash("abcde", 5) equals to 0x91aba2be);
      assert_that_size_t(komihash_hash("abcdef", 6) equals to 0xa7a03d16);
      assert_that_size_t(komihash_hash("abcdefg", 7) equals to 0x460093b1);
      assert_that_size_t(komihash_hash("abcdefgh", 8) equals to 0xf4fab7dc);
    });

    it("hashes medium sized strings", {
      assert_that_size_t(komihash_hash("abcdefghi", 9) equals to 0x199c8011);
      assert_that_size_t(komihash_hash("abcdefghij", 10) equals to 0xfe957747);
      assert_that_size_t(komihash_hash("abcdefghijk", 11) equals to 0x2c02eee1);
      assert_that_size_t(komihash_hash("abcdefghijkl", 12)
                           equals to 0x2bf7e6e4);
      assert_that_size_t(komihash_hash("abcdefghijklm", 13)
                           equals to 0x91c40eb2);
      assert_that_size_t(komihash_hash("abcdefghijklmn", 14)
                           equals to 0xe0bcb8e3);
      assert_that_size_t(komihash_hash("abcdefghijklmno", 15)
                           equals to 0xcd666237);
      assert_that_size_t(komihash_hash("abcdefghijklmnop", 16)
                           equals to 0x64188956);
    });

    it("hashes long strings", {
      assert_that_size_t(komihash_hash("abcdefghijklmnopqrst", 20)
                           equals to 0x40a44326);
      assert_that_size_t(komihash_hash(
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
        "ad minim veniam.",
        148
      ) equals to 0x6d10c0ba);
    });
  });
})

#endif
