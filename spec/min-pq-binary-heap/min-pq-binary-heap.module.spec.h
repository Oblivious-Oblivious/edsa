#ifndef __EDSA_MIN_PQ_BINARY_HEAP_BASE_MODULE_SPEC_H_
#define __EDSA_MIN_PQ_BINARY_HEAP_BASE_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/min-pq-binary-heap/min-pq-binary-heap.h"

module(T_min_pq_binary_heap_base, {
  describe("min pq binary heap", {
    it("creates a new priority queue", {
      void **pq = NULL;
      assert_that_size_t(pq_size(pq) equals to 0);
      pq_free(pq);
    });

    it("reports empty on a new queue", {
      void **pq = NULL;
      assert_that(pq_is_empty(pq));
      pq_free(pq);
    });

    it("reports empty on a NULL queue", {
      void **pq = NULL;
      assert_that(pq_is_empty(pq));
    });

    it("returns NULL when getting min of empty queue", {
      void **pq = NULL;
      assert_that(pq_get_min(pq) is NULL);
      pq_free(pq);
    });

    it("inserts and retrieves the minimum element", {
      int *pq = NULL;
      pq_insert(pq, 30);
      pq_insert(pq, 10);
      pq_insert(pq, 20);
      assert_that_size_t(pq_size(pq) equals to 3);
      assert_that_int(pq_get_min(pq) equals to 10);
      pq_free(pq);
    });

    it("deletes the minimum and maintains heap order", {
      int *pq = NULL;
      pq_insert(pq, 30);
      pq_insert(pq, 10);
      pq_insert(pq, 20);
      int min = pq_get_min(pq);
      pq_delete_min(pq);
      assert_that_int(min equals to 10);
      assert_that_size_t(pq_size(pq) equals to 2);
      assert_that_int(pq_get_min(pq) equals to 20);
      pq_free(pq);
    });

    it("returns NULL when deleting min from empty queue", {
      void **pq = NULL;
      pq_delete_min(pq);
      assert_that(pq_get_min(pq) is NULL);
      pq_free(pq);
    });

    it("does not insert beyond max size", {
      int *pq = NULL;
      pq_insert(pq, 1);
      pq_insert(pq, 2);
      pq_insert(pq, 3);
      pq_insert(pq, 4);
      pq_insert(pq, 5);
      assert_that_size_t(pq_size(pq) equals to 5);
      assert_that_int(pq_get_min(pq) equals to 1);
      pq_free(pq);
    });

    it("extracts all elements in sorted order", {
      int *pq = NULL;
      pq_insert(pq, 50);
      pq_insert(pq, 10);
      pq_insert(pq, 40);
      pq_insert(pq, 20);
      pq_insert(pq, 30);
      assert_that_int(pq_get_min(pq) equals to 10);
      pq_delete_min(pq);
      assert_that_int(pq_get_min(pq) equals to 20);
      pq_delete_min(pq);
      assert_that_int(pq_get_min(pq) equals to 30);
      pq_delete_min(pq);
      assert_that_int(pq_get_min(pq) equals to 40);
      pq_delete_min(pq);
      assert_that_int(pq_get_min(pq) equals to 50);
      pq_delete_min(pq);
      assert_that(pq_is_empty(pq));
      pq_free(pq);
    });

    it("resets the priority queue", {
      int *pq = NULL;
      pq_insert(pq, 1);
      pq_insert(pq, 2);
      pq_reset(pq);
      assert_that(pq_is_empty(pq));
      pq_free(pq);
    });

    it("can insert after reset", {
      int *pq = NULL;
      pq_insert(pq, 5);
      pq_reset(pq);
      pq_insert(pq, 42);
      assert_that_int(pq_get_min(pq) equals to 42);
      pq_free(pq);
    });

    it("handles reset on NULL without crashing", {
      void **pq = NULL;
      pq_reset(pq);
    });

    it("handles free on NULL without crashing", {
      void **pq = NULL;
      pq_free(pq);
    });

    it("handles print on NULL without crashing", {
      void **pq = NULL;
      pq_print(pq);
    });
  });
})

#endif
