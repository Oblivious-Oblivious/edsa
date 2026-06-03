#ifndef __EDSA_VECTOR_ALLOCATOR_MODULE_SPEC_H_
#define __EDSA_VECTOR_ALLOCATOR_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/arena.h"
#include "../../src/allocator/pool.h"
#include "../../src/allocator/utils.h"
#include "../../src/boolean/boolean.h"
#include "../../src/string/string-base.h"
#include "../../src/vector/vector.h"

#include <stdlib.h> /* malloc, free */

typedef struct VectorSpecRecord {
  char *name;
  char *description;
  int *numbers;
} VectorSpecRecord;

static void string_vector_free(void *allocator, void *ptr) {
  char **strings = ptr;
  size_t i;
  (void)allocator;
  for(i = 0; i < vector_size(strings); i++) {
    string_free(strings[i]);
  }
}


static void record_vector_free(void *allocator, void *ptr) {
  VectorSpecRecord *records = ptr;
  size_t i;
  (void)allocator;
  for(i = 0; i < vector_size(records); i++) {
    string_free(records[i].name);
    string_free(records[i].description);
    free(records[i].numbers);
  }
}

module(T_vector_allocator, {
  describe("vector allocator awareness", {
    context("#vector_set_allocator", {
      it("falls back to realloc and free without an allocator", {
        int *vv = NULL;

        vector_add(vv, 1);
        vector_add(vv, 2);
        assert_that_int(vector_size(vv) equals to 2);
        assert_that(_vector_get_header(vv)->allocator is NULL);
        assert_that(_vector_get_header(vv)->alloc is NULL);
        assert_that(_vector_get_header(vv)->free is NULL);

        vector_free(vv);
      });

      it("makes a NULL vector allocator aware from an arena", {
        unsigned char buffer[1024];
        AllocatorArena arena;
        int *vv = NULL;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        vector_set_allocator(vv, &arena, allocator_arena_alloc, NULL);

        assert_that(vv isnot NULL);
        assert_that(_vector_get_header(vv)->allocator is & arena);
        assert_that(_vector_get_header(vv)->alloc is allocator_arena_alloc);
        assert_that(_vector_get_header(vv)->free is NULL);
        assert_that((unsigned char *)_vector_get_header(vv) >= buffer);
        assert_that(
          (unsigned char *)_vector_get_header(vv) < buffer + sizeof(buffer)
        );

        vector_free(vv);
      });

      it("grows a vector backed by an arena and preserves its data", {
        unsigned char buffer[2048];
        AllocatorArena arena;
        int *vv = NULL;
        size_t i;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        vector_set_allocator(vv, &arena, allocator_arena_alloc, NULL);

        for(i = 0; i < 50; i++) {
          vector_add(vv, i);
        }
        assert_that_int(vector_size(vv) equals to 50);
        assert_that_int(vv[0] equals to 0);
        assert_that_int(vv[25] equals to 25);
        assert_that_int(vv[49] equals to 49);

        vector_free(vv);
        allocator_arena_free_all(&arena);

        vector_set_allocator(vv, &arena, allocator_arena_alloc, NULL);
        vector_add(vv, 1);
        assert_that_int(vv[0] equals to 1);

        vector_free(vv);
      });

      it("allocates a vector from a pool chunk", {
        unsigned char buffer[2048];
        AllocatorPool pool;
        int *vv = NULL;
        size_t i;

        allocator_pool_init(
          &pool, buffer, sizeof(buffer), 512, ALLOCATOR_DEFAULT_ALIGNMENT
        );
        vector_set_allocator(vv, &pool, allocator_pool_alloc, NULL);

        assert_that(vv isnot NULL);
        for(i = 0; i < 20; i++) {
          vector_add(vv, i);
        }
        assert_that_int(vector_size(vv) equals to 20);
        assert_that_int(vv[0] equals to 0);
        assert_that_int(vv[19] equals to 19);

        vector_free(vv);
        vector_set_allocator(vv, &pool, allocator_pool_alloc, NULL);
        vector_add(vv, 1);
        assert_that_int(vv[0] equals to 1);

        vector_free(vv);
      });

      it(
        "re-sets the allocator on an already allocated vector without growing",
        {
          unsigned char buffer[1024];
          AllocatorArena arena;
          int *vv = NULL;
          size_t capacity_before;

          allocator_arena_init(&arena, buffer, sizeof(buffer));
          vector_set_allocator(vv, &arena, allocator_arena_alloc, NULL);
          vector_add(vv, 1);
          vector_add(vv, 2);
          capacity_before = vector_capacity(vv);

          vector_set_allocator(vv, &arena, allocator_arena_alloc, NULL);
          assert_that_int(vector_size(vv) equals to 2);
          assert_that_size_t(vector_capacity(vv) equals to capacity_before);

          vector_free(vv);
        }
      );
    });

    context("on a custom free function", {
      it("frees a vector of edsa strings and their storage", {
        char **strings = NULL;

        vector_set_allocator(strings, NULL, NULL, string_vector_free);
        vector_add(strings, string_new("hello"));
        vector_add(strings, string_new("world"));
        vector_add(strings, string_new("vector"));

        assert_that_int(vector_size(strings) equals to 3);
        assert_that_charptr(strings[0] equals to "hello");
        assert_that_charptr(strings[1] equals to "world");
        assert_that_charptr(strings[2] equals to "vector");

        vector_free(strings);
        assert_that(strings is NULL);
      });

      it("frees a vector of records that own strings and allocations", {
        VectorSpecRecord *records = NULL;
        VectorSpecRecord first;
        VectorSpecRecord second;

        vector_set_allocator(records, NULL, NULL, record_vector_free);

        first.name        = string_new("Alice");
        first.description = string_new("first record");
        first.numbers     = malloc(3 * sizeof(int));
        first.numbers[0]  = 1;
        first.numbers[1]  = 2;
        first.numbers[2]  = 3;
        vector_add(records, first);

        second.name        = string_new("Bob");
        second.description = string_new("second record");
        second.numbers     = malloc(2 * sizeof(int));
        second.numbers[0]  = 4;
        second.numbers[1]  = 5;
        vector_add(records, second);

        assert_that_int(vector_size(records) equals to 2);
        assert_that_charptr(records[0].name equals to "Alice");
        assert_that_charptr(records[0].description equals to "first record");
        assert_that_charptr(records[1].name equals to "Bob");
        assert_that_charptr(records[1].description equals to "second record");
        assert_that_int(records[0].numbers[1] equals to 2);
        assert_that_int(records[1].numbers[0] equals to 4);

        vector_free(records);
        assert_that(records is NULL);
      });
    });
  });
})

#endif
