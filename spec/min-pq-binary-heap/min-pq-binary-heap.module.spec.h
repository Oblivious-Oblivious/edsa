#ifndef __EDSA_MIN_PQ_BINARY_HEAP_BASE_MODULE_SPEC_H_
#define __EDSA_MIN_PQ_BINARY_HEAP_BASE_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/min-pq-binary-heap/min-pq-binary-heap.h"

module(T_min_pq_binary_heap_base, {
  describe("min pq binary heap", {
    it("creates a new priority queue", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      assert_that(pq isnot NULL);
      assert_that_size_t(pq->size equals to 0);
      assert_that_size_t(pq->max_size equals to 10);
      pq_free(pq);
    });

    it("reports empty on a new queue", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      assert_that(pq_is_empty(pq));
      pq_free(pq);
    });

    it("reports empty on a NULL queue", { assert_that(pq_is_empty(NULL)); });

    it("returns NULL when getting min of empty queue", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      assert_that(pq_get_min(pq) is NULL);
      pq_free(pq);
    });

    it("inserts and retrieves the minimum element", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      pq_insert(pq, (void *)30);
      pq_insert(pq, (void *)10);
      pq_insert(pq, (void *)20);
      assert_that_size_t(pq->size equals to 3);
      assert_that(pq_get_min(pq) is(void *) 10);
      pq_free(pq);
    });

    it("deletes the minimum and maintains heap order", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      pq_insert(pq, (void *)30);
      pq_insert(pq, (void *)10);
      pq_insert(pq, (void *)20);
      void *min = pq_delete_min(pq);
      assert_that(min is(void *) 10);
      assert_that_size_t(pq->size equals to 2);
      assert_that(pq_get_min(pq) is(void *) 20);
      pq_free(pq);
    });

    it("returns NULL when deleting min from empty queue", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      assert_that(pq_delete_min(pq) is NULL);
      pq_free(pq);
    });

    it("does not insert beyond max size", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      pq_insert(pq, (void *)1);
      pq_insert(pq, (void *)2);
      pq_insert(pq, (void *)3);
      pq_insert(pq, (void *)4);
      pq_insert(pq, (void *)5);
      assert_that_size_t(pq->size equals to 5);
      assert_that(pq_get_min(pq) is(void *) 1);
      pq_free(pq);
    });

    it("extracts all elements in sorted order", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      pq_insert(pq, (void *)50);
      pq_insert(pq, (void *)10);
      pq_insert(pq, (void *)40);
      pq_insert(pq, (void *)20);
      pq_insert(pq, (void *)30);
      assert_that(pq_delete_min(pq) is(void *) 10);
      assert_that(pq_delete_min(pq) is(void *) 20);
      assert_that(pq_delete_min(pq) is(void *) 30);
      assert_that(pq_delete_min(pq) is(void *) 40);
      assert_that(pq_delete_min(pq) is(void *) 50);
      assert_that(pq_is_empty(pq));
      pq_free(pq);
    });

    it("resets the priority queue", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      pq_insert(pq, (void *)1);
      pq_insert(pq, (void *)2);
      pq_reset(pq);
      assert_that(pq_is_empty(pq));
      assert_that_size_t(pq->max_size equals to 10);
      pq_free(pq);
    });

    it("can insert after reset", {
      EdsaMinPQBinaryHeap *pq = pq_new(10);
      pq_insert(pq, (void *)5);
      pq_reset(pq);
      pq_insert(pq, (void *)42);
      assert_that(pq_get_min(pq) is(void *) 42);
      pq_free(pq);
    });

    it("handles reset on NULL without crashing", { pq_reset(NULL); });

    it("handles free on NULL without crashing", { pq_free(NULL); });

    it("handles print on NULL without crashing", { pq_print(NULL); });
  });
})

#endif
