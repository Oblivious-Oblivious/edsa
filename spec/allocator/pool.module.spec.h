#ifndef __EDSA_ALLOCATOR_POOL_MODULE_SPEC_H_
#define __EDSA_ALLOCATOR_POOL_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/allocator/pool.h"
#include "../../src/allocator/utils.h"

module(T_allocator_pool, {
  describe("#allocator_pool_init", {
    it("initializes the pool with aligned chunks from the backing buffer", {
      unsigned char buffer[64];
      AllocatorPool pool;
      size_t expected_chunk_size;

      allocator_pool_init(&pool, buffer, sizeof(buffer), 3, 8);
      expected_chunk_size = allocator_align_forward_size(3, 8);

      assert_that_size_t((uintptr_t)pool.buf equals to(uintptr_t) buffer);
      assert_that_size_t(pool.buf_len equals to sizeof(buffer));
      assert_that_size_t(pool.chunk_size equals to expected_chunk_size);
      assert_that(pool.head isnot NULL);
      assert_that_size_t((uintptr_t)pool.head % 8 equals to 0);
    });

    it("adjusts the usable buffer length when backing buffer is unaligned", {
      unsigned char buffer[65];
      AllocatorPool pool;
      unsigned char *unaligned_buffer;
      uintptr_t aligned_start;
      size_t expected_buffer_length;

      unaligned_buffer = buffer;
      while((uintptr_t)unaligned_buffer % 8 == 0) {
        unaligned_buffer++;
      }
      aligned_start = allocator_align_forward((uintptr_t)unaligned_buffer, 8);
      expected_buffer_length =
        64 - (size_t)(aligned_start - (uintptr_t)unaligned_buffer);

      allocator_pool_init(&pool, unaligned_buffer, 64, 8, 8);

      assert_that_size_t((uintptr_t)pool.buf equals to(uintptr_t)
                           unaligned_buffer);
      assert_that_size_t(pool.buf_len equals to expected_buffer_length);
    });
  });

  describe("#allocator_pool_alloc", {
    it("returns zeroed chunks from the free list", {
      unsigned char buffer[32];
      AllocatorPool pool;
      unsigned char *allocation;
      size_t i;

      memset(buffer, 0xFF, sizeof(buffer));
      allocator_pool_init(&pool, buffer, sizeof(buffer), 8, 8);

      allocation = allocator_pool_alloc(&pool, NULL, 8);

      assert_that(allocation isnot NULL);
      assert_that_size_t((uintptr_t)allocation % 8 equals to 0);
      for(i = 0; i < 8; i++) {
        assert_that_int(allocation[i] equals to 0);
      }
    });

    it("returns every chunk once before the pool is exhausted", {
      unsigned char buffer[32];
      AllocatorPool pool;
      void *first;
      void *second;
      void *third;
      void *fourth;

      allocator_pool_init(&pool, buffer, sizeof(buffer), 8, 8);

      first  = allocator_pool_alloc(&pool, NULL, 8);
      second = allocator_pool_alloc(&pool, NULL, 8);
      third  = allocator_pool_alloc(&pool, NULL, 8);
      fourth = allocator_pool_alloc(&pool, NULL, 8);

      assert_that(first isnot NULL);
      assert_that(second isnot NULL);
      assert_that(third isnot NULL);
      assert_that(fourth isnot NULL);
      assert_that(first isnot second);
      assert_that(first isnot third);
      assert_that(first isnot fourth);
      assert_that(second isnot third);
      assert_that(second isnot fourth);
      assert_that(third isnot fourth);
      assert_that(pool.head is NULL);
    });
  });

  describe("#allocator_pool_free", {
    it("reuses the most recently freed chunk", {
      unsigned char buffer[32];
      AllocatorPool pool;
      void *first;
      void *second;
      void *reused;

      allocator_pool_init(&pool, buffer, sizeof(buffer), 8, 8);
      first  = allocator_pool_alloc(&pool, NULL, 8);
      second = allocator_pool_alloc(&pool, NULL, 8);

      allocator_pool_free(&pool, first);
      allocator_pool_free(&pool, second);
      reused = allocator_pool_alloc(&pool, NULL, 8);

      assert_that(reused is second);
    });

    it("ignores NULL pointers", {
      unsigned char buffer[16];
      AllocatorPool pool;
      AllocatorPoolFreeNode *head;

      allocator_pool_init(&pool, buffer, sizeof(buffer), 8, 8);
      head = pool.head;

      allocator_pool_free(&pool, NULL);

      assert_that(pool.head is head);
    });
  });

  describe("#allocator_pool_free_all", {
    it("rebuilds the free list for all chunks", {
      unsigned char buffer[24];
      AllocatorPool pool;
      void *first;
      void *second;
      void *third;

      allocator_pool_init(&pool, buffer, sizeof(buffer), 8, 8);
      allocator_pool_alloc(&pool, NULL, 8);
      allocator_pool_alloc(&pool, NULL, 8);
      allocator_pool_alloc(&pool, NULL, 8);
      assert_that(pool.head is NULL);

      allocator_pool_free_all(&pool);

      first  = allocator_pool_alloc(&pool, NULL, 8);
      second = allocator_pool_alloc(&pool, NULL, 8);
      third  = allocator_pool_alloc(&pool, NULL, 8);

      assert_that(first isnot NULL);
      assert_that(second isnot NULL);
      assert_that(third isnot NULL);
      assert_that(first isnot second);
      assert_that(first isnot third);
      assert_that(second isnot third);
      assert_that(pool.head is NULL);
    });
  });

  it("executes an end to end test", {
    unsigned char backing_buffer[1024];
    AllocatorPool p;
    void *a, *b, *c, *d, *e, *f;

    allocator_pool_init(
      &p, backing_buffer, 1024, 64, ALLOCATOR_DEFAULT_ALIGNMENT
    );

    a = allocator_pool_alloc(&p, NULL, 64);
    b = allocator_pool_alloc(&p, NULL, 64);
    c = allocator_pool_alloc(&p, NULL, 64);
    d = allocator_pool_alloc(&p, NULL, 64);
    e = allocator_pool_alloc(&p, NULL, 64);
    f = allocator_pool_alloc(&p, NULL, 64);

    allocator_pool_free(&p, f);
    allocator_pool_free(&p, c);
    allocator_pool_free(&p, b);
    allocator_pool_free(&p, d);

    d = allocator_pool_alloc(&p, NULL, 64);
    assert_that(d isnot NULL);
    assert_that(d isnot a);
    assert_that(d isnot b);
    assert_that(d isnot c);
    assert_that(d isnot e);
    assert_that(d isnot f);

    allocator_pool_free(&p, a);

    a = allocator_pool_alloc(&p, NULL, 64);
    assert_that(a isnot NULL);
    assert_that(a isnot b);
    assert_that(a isnot c);
    assert_that(a isnot d);
    assert_that(a isnot e);
    assert_that(a isnot f);

    allocator_pool_free(&p, e);
    allocator_pool_free(&p, a);
    allocator_pool_free(&p, d);

    assert_that(allocator_pool_alloc(&p, NULL, 64) is d);
    assert_that(allocator_pool_alloc(&p, NULL, 64) is a);
    assert_that(allocator_pool_alloc(&p, NULL, 64) is e);
  });
})

#endif
