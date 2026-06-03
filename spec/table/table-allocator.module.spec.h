#ifndef __EDSA_TABLE_ALLOCATOR_MODULE_SPEC_H_
#define __EDSA_TABLE_ALLOCATOR_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/arena.h"
#include "../../src/allocator/pool.h"
#include "../../src/allocator/utils.h"
#include "../../src/string/string-base.h"
#include "../../src/table/table.h"
#include "../../src/vector/vector.h"

module(T_table_allocator, {
  describe("table allocator awareness", {
    context("#table_set_allocator", {
      it("falls back to realloc and free without an allocator", {
        EdsaTable table = {0};
        table_init(&table);

        table_add(&table, "key1", 100);
        assert_that_size_t(table_get(&table, "key1") equals to 100);
        assert_that(table.allocator is NULL);
        assert_that(table.alloc_fn is NULL);
        assert_that(table.free_fn is NULL);

        table_deinit(&table);
      });

      it("makes a table backed by an arena", {
        unsigned char buffer[65536];
        AllocatorArena arena;
        EdsaTable table = {0};

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        table_init(&table);
        table_set_allocator(&table, &arena, allocator_arena_alloc, NULL);

        assert_that(table.allocator is & arena);
        assert_that(table.alloc_fn is allocator_arena_alloc);
        assert_that(_vector_get_header(table.keys)->allocator is & arena);
        assert_that(_vector_get_header(table.values)->allocator is & arena);
        assert_that(_vector_get_header(table.hashes)->allocator is & arena);
        assert_that(_vector_get_header(table.states)->allocator is & arena);

        table_add(&table, "hello", 1);
        table_add(&table, "world", 2);
        assert_that_size_t(table_get(&table, "hello") equals to 1);
        assert_that_size_t(table_get(&table, "world") equals to 2);
        assert_that_size_t(table_size(&table) equals to 2);

        table_deinit(&table);
      });

      it("grows a table backed by an arena and reuses after arena reset", {
        unsigned char buffer[524288];
        AllocatorArena arena;
        EdsaTable table = {0};
        char **keys     = NULL;
        size_t i;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        table_init(&table);
        table_set_allocator(&table, &arena, allocator_arena_alloc, NULL);

        for(i = 0; i < 2000; i++) {
          char key[32];
          snprintf(key, sizeof(key), "key_%zu", i);
          vector_add(keys, string_new(key));
          table_add(&table, keys[i], i);
        }
        assert_that_size_t(table_size(&table) equals to 2000);
        assert_that_size_t(table_get(&table, keys[0]) equals to 0);
        assert_that_size_t(table_get(&table, keys[999]) equals to 999);
        assert_that_size_t(table_get(&table, keys[1999]) equals to 1999);

        table_deinit(&table);
        for(i = 0; i < vector_size(keys); i++) {
          string_free(keys[i]);
        }
        vector_free(keys);

        allocator_arena_free_all(&arena);
        table_init(&table);
        table_set_allocator(&table, &arena, allocator_arena_alloc, NULL);
        table_add(&table, "fresh", 1);
        assert_that_size_t(table_get(&table, "fresh") equals to 1);

        table_deinit(&table);
      });

      it("allocates a table from a pool and reuses after pool reset", {
        unsigned char buffer[131072];
        AllocatorPool pool;
        EdsaTable table = {0};

        allocator_pool_init(
          &pool, buffer, sizeof(buffer), 65536, ALLOCATOR_DEFAULT_ALIGNMENT
        );
        table_init(&table);
        table_set_allocator(&table, &pool, allocator_pool_alloc, NULL);

        table_add(&table, "alpha", 10);
        table_add(&table, "beta", 20);
        assert_that_size_t(table_get(&table, "alpha") equals to 10);
        assert_that_size_t(table_get(&table, "beta") equals to 20);

        table_remove(&table, "alpha");
        assert_that_size_t(table_get(&table, "alpha")
                             equals to TABLE_UNDEFINED);

        table_deinit(&table);

        allocator_pool_free_all(&pool);
        table_init(&table);
        table_set_allocator(&table, &pool, allocator_pool_alloc, NULL);
        table_add(&table, "gamma", 30);
        assert_that_size_t(table_get(&table, "gamma") equals to 30);

        table_deinit(&table);
      });

      it("re-sets the allocator on an already initialized table", {
        unsigned char buffer[65536];
        AllocatorArena arena;
        EdsaTable table = {0};

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        table_init(&table);
        table_add(&table, "before", 1);

        table_set_allocator(&table, &arena, allocator_arena_alloc, NULL);
        assert_that_size_t(table_get(&table, "before") equals to 1);

        table_add(&table, "after", 2);
        assert_that_size_t(table_get(&table, "after") equals to 2);
        assert_that_size_t(table_size(&table) equals to 2);

        table_deinit(&table);
      });

      it("clears the allocator and resets the table to a fresh state", {
        unsigned char buffer[65536];
        AllocatorArena arena;
        EdsaTable table = {0};

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        table_init(&table);
        table_set_allocator(&table, &arena, allocator_arena_alloc, NULL);

        table_add(&table, "one", 1);
        table_add(&table, "two", 2);
        table_add(&table, "three", 3);
        assert_that_size_t(table_size(&table) equals to 3);
        assert_that_size_t(table_get(&table, "one") equals to 1);
        assert_that_size_t(table_get(&table, "two") equals to 2);
        assert_that_size_t(table_get(&table, "three") equals to 3);

        table_deinit(&table);
        assert_that(table.allocator is NULL);
        assert_that(table.alloc_fn is NULL);
        assert_that(table.free_fn is NULL);
        assert_that(table.keys is NULL);
        assert_that(table.values is NULL);
        assert_that(table.hashes is NULL);
        assert_that(table.states is NULL);
        assert_that_size_t(table.size equals to 0);
        assert_that_size_t(table.tombstones equals to 0);

        table_init(&table);
        assert_that_size_t(table_size(&table) equals to 0);
        assert_that_size_t(table_get(&table, "one") equals to TABLE_UNDEFINED);

        table_deinit(&table);
      });
    });
  });
})

#endif
