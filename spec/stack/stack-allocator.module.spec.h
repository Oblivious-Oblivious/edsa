#ifndef __EDSA_STACK_ALLOCATOR_MODULE_SPEC_H_
#define __EDSA_STACK_ALLOCATOR_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/arena.h"
#include "../../src/allocator/pool.h"
#include "../../src/allocator/utils.h"
#include "../../src/stack/stack.h"
#include "../../src/string/string-base.h"
#include "../../src/vector/vector.h"

#include <stdlib.h> /* malloc, free */

typedef struct StackSpecRecord {
  char *name;
  char *description;
  int *numbers;
} StackSpecRecord;

static void string_stack_free(void *allocator, void *ptr) {
  char **strings = ptr;
  size_t i;
  (void)allocator;
  for(i = 0; i < vector_size(strings); i++) {
    string_free(strings[i]);
  }
}

static void record_stack_free(void *allocator, void *ptr) {
  StackSpecRecord *records = ptr;
  size_t i;
  (void)allocator;
  for(i = 0; i < vector_size(records); i++) {
    string_free(records[i].name);
    string_free(records[i].description);
    free(records[i].numbers);
  }
}

module(T_stack_allocator, {
  describe("stack allocator awareness", {
    context("#stack_set_allocator", {
      it("falls back to realloc and free without an allocator", {
        int *st = NULL;

        stack_push(st, 1);
        stack_push(st, 2);
        assert_that_int(stack_size(st) equals to 2);
        assert_that(_vector_get_header(st)->allocator is NULL);
        assert_that(_vector_get_header(st)->alloc is NULL);
        assert_that(_vector_get_header(st)->free is NULL);

        stack_free(st);
      });

      it("makes a stack backed by an arena and preserves push/pop", {
        unsigned char buffer[2048];
        AllocatorArena arena;
        int *st = NULL;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        stack_set_allocator(st, &arena, allocator_arena_alloc, NULL);

        stack_push(st, 10);
        stack_push(st, 20);
        stack_push(st, 30);
        assert_that_int(stack_size(st) equals to 3);
        assert_that_int(stack_pop(st) equals to 30);
        assert_that_int(stack_pop(st) equals to 20);
        assert_that_int(stack_pop(st) equals to 10);
        assert_that(stack_is_empty(st));

        stack_free(st);
      });

      it("grows a stack backed by an arena and reuses after arena reset", {
        unsigned char buffer[2048];
        AllocatorArena arena;
        int *st = NULL;
        size_t i;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        stack_set_allocator(st, &arena, allocator_arena_alloc, NULL);

        for(i = 0; i < 50; i++) {
          stack_push(st, i);
        }
        assert_that_int(stack_size(st) equals to 50);
        assert_that_int(st[0] equals to 0);
        assert_that_int(st[25] equals to 25);
        assert_that_int(st[49] equals to 49);

        stack_free(st);
        allocator_arena_free_all(&arena);

        stack_set_allocator(st, &arena, allocator_arena_alloc, NULL);
        stack_push(st, 1);
        assert_that_int(st[0] equals to 1);

        stack_free(st);
      });

      it("allocates a stack from a pool chunk", {
        unsigned char buffer[2048];
        AllocatorPool pool;
        int *st = NULL;
        size_t i;

        allocator_pool_init(
          &pool, buffer, sizeof(buffer), 512, ALLOCATOR_DEFAULT_ALIGNMENT
        );
        stack_set_allocator(st, &pool, allocator_pool_alloc, NULL);

        assert_that(st isnot NULL);
        for(i = 0; i < 20; i++) {
          stack_push(st, i);
        }
        assert_that_int(stack_size(st) equals to 20);
        assert_that_int(st[0] equals to 0);
        assert_that_int(st[19] equals to 19);

        stack_free(st);
        stack_set_allocator(st, &pool, allocator_pool_alloc, NULL);
        stack_push(st, 1);
        assert_that_int(st[0] equals to 1);

        stack_free(st);
      });

      it(
        "re-sets the allocator on an already allocated stack without growing", {
          unsigned char buffer[1024];
          AllocatorArena arena;
          int *st = NULL;
          size_t capacity_before;

          allocator_arena_init(&arena, buffer, sizeof(buffer));
          stack_set_allocator(st, &arena, allocator_arena_alloc, NULL);
          stack_push(st, 1);
          stack_push(st, 2);
          capacity_before = vector_capacity(st);

          stack_set_allocator(st, &arena, allocator_arena_alloc, NULL);
          assert_that_int(stack_size(st) equals to 2);
          assert_that_size_t(vector_capacity(st) equals to capacity_before);

          stack_free(st);
        }
      );
    });

    context("on a custom free function", {
      it("frees a stack of edsa strings and their storage", {
        char **st = NULL;

        stack_set_allocator(st, NULL, NULL, string_stack_free);
        stack_push(st, string_new("hello"));
        stack_push(st, string_new("world"));
        stack_push(st, string_new("stack"));

        assert_that_int(stack_size(st) equals to 3);
        assert_that_charptr(st[0] equals to "hello");
        assert_that_charptr(st[1] equals to "world");
        assert_that_charptr(st[2] equals to "stack");

        stack_free(st);
        assert_that(st is NULL);
      });

      it("frees a stack of records that own strings and allocations", {
        StackSpecRecord *st = NULL;
        StackSpecRecord first;
        StackSpecRecord second;

        stack_set_allocator(st, NULL, NULL, record_stack_free);

        first.name        = string_new("Alice");
        first.description = string_new("first record");
        first.numbers     = malloc(3 * sizeof(int));
        first.numbers[0]  = 1;
        first.numbers[1]  = 2;
        first.numbers[2]  = 3;
        stack_push(st, first);

        second.name        = string_new("Bob");
        second.description = string_new("second record");
        second.numbers     = malloc(2 * sizeof(int));
        second.numbers[0]  = 4;
        second.numbers[1]  = 5;
        stack_push(st, second);

        assert_that_int(stack_size(st) equals to 2);
        assert_that_charptr(st[0].name equals to "Alice");
        assert_that_charptr(st[0].description equals to "first record");
        assert_that_charptr(st[1].name equals to "Bob");
        assert_that_charptr(st[1].description equals to "second record");
        assert_that_int(st[0].numbers[1] equals to 2);
        assert_that_int(st[1].numbers[0] equals to 4);

        stack_free(st);
        assert_that(st is NULL);
      });
    });
  });
})

#endif
