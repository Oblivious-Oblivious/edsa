#ifndef __EDSA_ALLOCATOR_ARENA_MODULE_SPEC_H_
#define __EDSA_ALLOCATOR_ARENA_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/arena.h"
#include "../../src/allocator/utils.h"

#include <stdint.h>

module(T_allocator_arena, {
  describe("#allocator_arena_init", {
    it("initializes the arena with the provided backing buffer", {
      unsigned char buffer[64];
      AllocatorArena arena;

      allocator_arena_init(&arena, buffer, sizeof(buffer));

      assert_that(arena.buf is buffer);
      assert_that_size_t(arena.buf_len equals to sizeof(buffer));
      assert_that_size_t(arena.curr_offset equals to 0);
      assert_that_size_t(arena.prev_offset equals to 0);
    });
  });

  describe("#allocator_arena_alloc", {
    it("returns zeroed memory from the backing buffer", {
      unsigned char buffer[64];
      AllocatorArena arena;
      unsigned char *allocation;

      allocator_arena_init(&arena, buffer, sizeof(buffer));
      allocation = allocator_arena_alloc(&arena, NULL, 4);

      assert_that(allocation isnot NULL);
      assert_that(allocation is buffer);
      assert_that_size_t(arena.prev_offset equals to 0);
      assert_that_size_t(arena.curr_offset equals to 4);
      assert_that_int(allocation[0] equals to 0);
      assert_that_int(allocation[1] equals to 0);
      assert_that_int(allocation[2] equals to 0);
      assert_that_int(allocation[3] equals to 0);
    });

    it("aligns each allocation to the default alignment", {
      unsigned char buffer[64];
      AllocatorArena arena;
      void *first;
      void *second;

      allocator_arena_init(&arena, buffer, sizeof(buffer));
      first  = allocator_arena_alloc(&arena, NULL, 1);
      second = allocator_arena_alloc(&arena, NULL, 1);

      assert_that(first isnot NULL);
      assert_that(second isnot NULL);
      assert_that_size_t(
        (uintptr_t)first % ALLOCATOR_DEFAULT_ALIGNMENT equals to 0
      );
      assert_that_size_t(
        (uintptr_t)second % ALLOCATOR_DEFAULT_ALIGNMENT equals to 0
      );
      assert_that_size_t(
        arena.prev_offset equals to ALLOCATOR_DEFAULT_ALIGNMENT
      );
      assert_that_size_t(
        arena.curr_offset equals to ALLOCATOR_DEFAULT_ALIGNMENT + 1
      );
    });

    it("returns NULL when there is not enough backing memory", {
      unsigned char buffer[8];
      AllocatorArena arena;

      allocator_arena_init(&arena, buffer, sizeof(buffer));

      assert_that(allocator_arena_alloc(&arena, NULL, sizeof(buffer) + 1)
                    is NULL);
      assert_that_size_t(arena.curr_offset equals to 0);
      assert_that_size_t(arena.prev_offset equals to 0);
    });
  });

  describe("#allocator_arena_free_all", {
    it("resets arena offsets", {
      unsigned char buffer[64];
      AllocatorArena arena;

      allocator_arena_init(&arena, buffer, sizeof(buffer));
      allocator_arena_alloc(&arena, NULL, 4);
      allocator_arena_free_all(&arena);

      assert_that_size_t(arena.prev_offset equals to 0);
      assert_that_size_t(arena.curr_offset equals to 0);
    });
  });

  it("performs a complete end to end test", {
    int i;

    unsigned char backing_buffer[256];
    AllocatorArena a = {0};
    allocator_arena_init(&a, backing_buffer, 256);

    for(i = 0; i < 10; i++) {
      int *x;
      float *f;
      char *str;

      // Reset all arena offsets for each loop
      allocator_arena_free_all(&a);

      x   = (int *)allocator_arena_alloc(&a, NULL, sizeof(int));
      f   = (float *)allocator_arena_alloc(&a, NULL, sizeof(float));
      str = allocator_arena_alloc(&a, NULL, 10);

      *x = 123;
      *f = 987;
      memmove(str, "Hellope", 7);

      assert_that_int(*x equals to 123);
      assert_that_float(*f equals to 987);
      assert_that_charptr(str equals to "Hellope");

      str = allocator_arena_alloc(&a, str, 16);
      memmove(str + 7, " world!", 7);

      assert_that_charptr(str equals to "Hellope world!");
    }

    allocator_arena_free_all(&a);
  });
})

#endif
