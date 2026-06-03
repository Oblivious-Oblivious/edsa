#ifndef __EDSA_LINKED_LIST_ALLOCATOR_MODULE_SPEC_H_
#define __EDSA_LINKED_LIST_ALLOCATOR_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/arena.h"
#include "../../src/allocator/pool.h"
#include "../../src/allocator/utils.h"
#include "../../src/linked-list/linked-list-base.h"
#include "../../src/string/string-base.h"

#include <stdlib.h> /* malloc, free */

static void string_ll_free(void *allocator, void *item) {
  char *str = item;
  (void)allocator;
  string_free(str);
}

module(T_linked_list_allocator, {
  describe("linked list allocator awareness", {
    context("#linked_list_set_allocator", {
      it("falls back to realloc and free without an allocator", {
        EdsaLinkedList *l = linked_list_new();
        linked_list_add(l, (void *)1);
        linked_list_add(l, (void *)2);
        assert_that_size_t(l->length equals to 2);
        assert_that(l->allocator is NULL);
        assert_that(l->alloc_fn is NULL);
        assert_that(l->free_fn is NULL);

        linked_list_free(l);
      });

      it("makes a linked list backed by an arena", {
        unsigned char buffer[4096];
        AllocatorArena arena;
        EdsaLinkedList *l = linked_list_new();

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        linked_list_set_allocator(l, &arena, allocator_arena_alloc, NULL);

        assert_that(l->allocator is & arena);
        assert_that(l->alloc_fn is allocator_arena_alloc);

        linked_list_add(l, (void *)10);
        linked_list_add(l, (void *)20);
        linked_list_add(l, (void *)30);
        assert_that_size_t(l->length equals to 3);
        assert_that(l->head->item is(void *) 10);
        assert_that(l->head->next->item is(void *) 20);
        assert_that(l->head->next->next->item is(void *) 30);

        linked_list_free(l);
      });

      it("removes a node from an arena-backed list", {
        unsigned char buffer[4096];
        AllocatorArena arena;
        EdsaLinkedList *l = linked_list_new();

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        linked_list_set_allocator(l, &arena, allocator_arena_alloc, NULL);

        linked_list_add(l, (void *)1);
        linked_list_add(l, (void *)2);
        linked_list_add(l, (void *)3);
        linked_list_remove(l, (void *)2);
        assert_that_size_t(l->length equals to 2);
        assert_that(l->head->item is(void *) 1);
        assert_that(l->head->next->item is(void *) 3);

        linked_list_free(l);
      });

      it("allocates a linked list from a pool", {
        unsigned char buffer[8192];
        AllocatorPool pool;
        EdsaLinkedList *l = linked_list_new();

        allocator_pool_init(
          &pool, buffer, sizeof(buffer), 256, ALLOCATOR_DEFAULT_ALIGNMENT
        );
        linked_list_set_allocator(l, &pool, allocator_pool_alloc, NULL);

        linked_list_add(l, (void *)100);
        linked_list_add(l, (void *)200);
        assert_that_size_t(l->length equals to 2);
        assert_that(l->head->item is(void *) 100);
        assert_that(l->head->next->item is(void *) 200);

        linked_list_free(l);
      });

      it("frees and re-allocates from a reset arena", {
        unsigned char buffer[8192];
        AllocatorArena arena;
        EdsaLinkedList *l;

        allocator_arena_init(&arena, buffer, sizeof(buffer));

        l = linked_list_new();
        linked_list_set_allocator(l, &arena, allocator_arena_alloc, NULL);
        linked_list_add(l, (void *)1);
        assert_that_size_t(l->length equals to 1);
        linked_list_free(l);

        allocator_arena_free_all(&arena);

        l = linked_list_new();
        linked_list_set_allocator(l, &arena, allocator_arena_alloc, NULL);
        linked_list_add(l, (void *)2);
        assert_that_size_t(l->length equals to 1);
        assert_that(l->head->item is(void *) 2);
        linked_list_free(l);
      });
    });

    context("on a custom free function", {
      it("frees a linked list of edsa strings using free_fn", {
        EdsaLinkedList *l = linked_list_new();
        linked_list_set_allocator(l, NULL, NULL, string_ll_free);

        linked_list_add(l, string_new("hello"));
        linked_list_add(l, string_new("world"));
        assert_that_size_t(l->length equals to 2);
        assert_that_charptr((char *)l->head->item equals to "hello");
        assert_that_charptr((char *)l->head->next->item equals to "world");

        linked_list_free(l);
      });
    });
  });
})

#endif
