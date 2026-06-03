#ifndef __EDSA_MIN_PQ_BINARY_HEAP_ALLOCATOR_MODULE_SPEC_H_
#define __EDSA_MIN_PQ_BINARY_HEAP_ALLOCATOR_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/arena.h"
#include "../../src/allocator/pool.h"
#include "../../src/allocator/utils.h"
#include "../../src/min-pq-binary-heap/min-pq-binary-heap.h"
#include "../../src/vector/vector.h"

module(T_min_pq_binary_heap_allocator, {
  describe("min pq binary heap allocator awareness", {
    context("#pq_set_allocator", {
      it("falls back to realloc and free without an allocator", {
        int *pq = NULL;

        pq_insert(pq, 1);
        pq_insert(pq, 2);
        assert_that_size_t(pq_size(pq) equals to 2);
        assert_that(_vector_get_header(pq)->allocator is NULL);
        assert_that(_vector_get_header(pq)->alloc is NULL);
        assert_that(_vector_get_header(pq)->free is NULL);

        pq_free(pq);
      });

      it("makes a pq backed by an arena", {
        unsigned char buffer[4096];
        AllocatorArena arena;
        int *pq = NULL;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        pq_set_allocator(pq, &arena, allocator_arena_alloc, NULL);

        pq_insert(pq, 30);
        pq_insert(pq, 10);
        pq_insert(pq, 20);
        assert_that_size_t(pq_size(pq) equals to 3);
        assert_that_int(pq_get_min(pq) equals to 10);
        assert_that(_vector_get_header(pq)->allocator is & arena);

        pq_free(pq);
      });

      it("grows a pq backed by an arena and reuses after reset", {
        unsigned char buffer[16384];
        AllocatorArena arena;
        int *pq = NULL;
        size_t i;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        pq_set_allocator(pq, &arena, allocator_arena_alloc, NULL);

        for(i = 0; i < 100; i++) {
          pq_insert(pq, 100 - i);
        }
        assert_that_size_t(pq_size(pq) equals to 100);
        assert_that_int(pq_get_min(pq) equals to 1);

        pq_free(pq);
        allocator_arena_free_all(&arena);

        pq_set_allocator(pq, &arena, allocator_arena_alloc, NULL);
        pq_insert(pq, 42);
        assert_that_int(pq_get_min(pq) equals to 42);

        pq_free(pq);
      });

      it("allocates a pq from a pool and reuses after pool reset", {
        unsigned char buffer[8192];
        AllocatorPool pool;
        int *pq = NULL;

        allocator_pool_init(
          &pool, buffer, sizeof(buffer), 4096, ALLOCATOR_DEFAULT_ALIGNMENT
        );
        pq_set_allocator(pq, &pool, allocator_pool_alloc, NULL);

        pq_insert(pq, 5);
        pq_insert(pq, 3);
        pq_insert(pq, 7);
        assert_that_int(pq_get_min(pq) equals to 3);

        pq_free(pq);

        allocator_pool_free_all(&pool);
        pq_set_allocator(pq, &pool, allocator_pool_alloc, NULL);
        pq_insert(pq, 99);
        assert_that_int(pq_get_min(pq) equals to 99);

        pq_free(pq);
      });

      it("re-sets the allocator on an already allocated pq without growing", {
        unsigned char buffer[4096];
        AllocatorArena arena;
        int *pq = NULL;
        size_t capacity_before;

        allocator_arena_init(&arena, buffer, sizeof(buffer));
        pq_set_allocator(pq, &arena, allocator_arena_alloc, NULL);
        pq_insert(pq, 1);
        pq_insert(pq, 2);
        capacity_before = vector_capacity(pq);

        pq_set_allocator(pq, &arena, allocator_arena_alloc, NULL);
        assert_that_size_t(pq_size(pq) equals to 2);
        assert_that_size_t(vector_capacity(pq) equals to capacity_before);

        pq_free(pq);
      });
    });
  });
})

#endif
