#ifndef __EDSA_STRING_ALLOCATOR_MODULE_SPEC_H_
#define __EDSA_STRING_ALLOCATOR_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/arena.h"
#include "../../src/allocator/pool.h"
#include "../../src/allocator/utils.h"
#include "../../src/string/string-base.h"
#include "../../src/vector/vector.h"

module(T_string_allocator, {
  describe("string allocator awareness", {
    context("on default allocation (no custom allocator)", {
      it("creates a string with default realloc/free", {
        char *str = string_new("hello");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "hello");
        assert_that(_vector_get_header(str)->allocator is NULL);
        assert_that(_vector_get_header(str)->alloc is NULL);

        string_free(str);
      });
    });

    context("#string_set_allocator", {
      it("makes a string backed by an arena", {
        unsigned char buffer[4096];
        AllocatorArena arena;
        char *str = NULL;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        string_set_allocator(str, &arena, allocator_arena_alloc, NULL);

        string_add(str, "hello");
        string_add(str, " world");
        assert_that(str isnot NULL);
        assert_that_charptr(str equals to "hello world");
        assert_that_int(string_size(str) equals to 11);
        assert_that(_vector_get_header(str)->allocator is & arena);
        assert_that(_vector_get_header(str)->alloc is allocator_arena_alloc);

        string_free(str);
      });

      it("grows a string backed by an arena beyond initial capacity", {
        unsigned char buffer[8192];
        AllocatorArena arena;
        char *str = NULL;
        size_t i;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        string_set_allocator(str, &arena, allocator_arena_alloc, NULL);

        for(i = 0; i < 100; i++) {
          string_add(str, "x");
        }
        assert_that_int(string_size(str) equals to 100);
        assert_that(_vector_get_header(str)->allocator is & arena);

        string_free(str);
      });

      it("allocates a string from a pool chunk", {
        unsigned char buffer[8192];
        AllocatorPool pool;
        char *str = NULL;

        allocator_pool_init(
          &pool, buffer, sizeof(buffer), 4096, ALLOCATOR_DEFAULT_ALIGNMENT
        );
        string_set_allocator(str, &pool, allocator_pool_alloc, NULL);

        string_add(str, "pooled");
        assert_that_charptr(str equals to "pooled");
        assert_that(_vector_get_header(str)->allocator is & pool);

        string_free(str);
      });

      it("uses string_addf with an arena-backed string", {
        unsigned char buffer[4096];
        AllocatorArena arena;
        char *str = NULL;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        string_set_allocator(str, &arena, allocator_arena_alloc, NULL);

        string_addf(&str, "value: %d", 42);
        assert_that_charptr(str equals to "value: 42");
        assert_that(_vector_get_header(str)->allocator is & arena);

        string_free(str);
      });

      it("performs string_shorten and string_skip_first on arena string", {
        unsigned char buffer[4096];
        AllocatorArena arena;
        char *str = NULL;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        string_set_allocator(str, &arena, allocator_arena_alloc, NULL);

        string_add(str, "hello world");
        string_shorten(str, 5);
        assert_that_charptr(str equals to "hello");

        string_skip_first(str, 2);
        assert_that_charptr(str equals to "llo");

        string_free(str);
      });

      it("frees and re-allocates a string from a reset arena", {
        unsigned char buffer[4096];
        AllocatorArena arena;
        char *str = NULL;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        string_set_allocator(str, &arena, allocator_arena_alloc, NULL);
        string_add(str, "first");
        assert_that_charptr(str equals to "first");

        string_free(str);
        allocator_arena_free_all(&arena);

        string_set_allocator(str, &arena, allocator_arena_alloc, NULL);
        string_add(str, "second");
        assert_that_charptr(str equals to "second");

        string_free(str);
      });
    });
  });
})

#endif
