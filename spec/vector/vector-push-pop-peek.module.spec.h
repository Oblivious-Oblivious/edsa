#ifndef __EDSA_VECTOR_PUSH_POP_PEEK_MODULE_SPEC_H_
#define __EDSA_VECTOR_PUSH_POP_PEEK_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/vector/vector.h"

module(T_vector_push_pop_peek, {
  describe("#push", {
    it("pushes 3 elements to the end of the vector", {
      int *v = NULL;
      vector_push(v, 1);
      vector_push(v, 2);
      vector_push(v, 4);
      assert_that_int(v[0] equals to 1);
      assert_that_int(v[1] equals to 2);
      assert_that_int(v[2] equals to 4);
      assert_that(vector_size(v) is 3);
      vector_free(v);
    });
  });

  describe("#pop", {
    it("pushes 3 elements and pops the 2 last", {
      int *v = NULL;
      vector_push(v, 1);
      vector_push(v, 2);
      vector_push(v, 4);
      int res1 = vector_pop(v);
      int res2 = vector_pop(v);
      assert_that_int(res1 equals to 4);
      assert_that_int(res2 equals to 2);
      assert_that(vector_size(v) is 1);
      vector_free(v);
    });
  });

  describe("#peek", {
    it("pushes elements and correctly peeks the top (last element)", {
      int *v = NULL;
      vector_push(v, 1);
      int res1 = vector_peek(v);
      vector_push(v, 2);
      int res2 = vector_peek(v);
      vector_push(v, 4);
      int res3 = vector_peek(v);
      assert_that_int(res1 equals to 1);
      assert_that_int(res2 equals to 2);
      assert_that_int(res3 equals to 4);
      assert_that(vector_size(v) is 3);
      vector_free(v);
    });
  });

  describe("stack data structure", {
    int *st = NULL;

    it("asserts that a new vector is empty", {
      assert_that(vector_is_empty(st));
    });

    it("pushes an element into the vector", {
      vector_push(st, 0);
      nassert_that(vector_is_empty(st));
    });

    it("pops an empty vector and returns NULL", {
      assert_that_int(vector_pop(st) equals to 0);
    });

    it("is empty after 1 push and 1 pop", {
      vector_push(st, 0);
      int res = vector_pop(st);
      assert_that(res is 0);
      assert_that(vector_is_empty(st));
    });

    it("is not empty after 2 pushes and 1 pop", {
      vector_push(st, 0);
      vector_push(st, 0);
      int res = vector_pop(st);
      assert_that(res is 0);
      nassert_that(vector_is_empty(st));
    });

    it("pops `x` after pushing `x`", {
      vector_push(st, 99);
      assert_that_int(vector_pop(st) equals to 99);
      vector_push(st, 88);
      assert_that_int(vector_pop(st) equals to 88);
    });

    it("pops `y` then `x` after pushing `x` then `y`", {
      vector_push(st, 99);
      vector_push(st, 88);
      assert_that_int(vector_pop(st) equals to 88);
      assert_that_int(vector_pop(st) equals to 99);
    });

    it("pops more elements than the size of the vector", {
      int *st = NULL;
      vector_push(st, 1);
      vector_push(st, 2);
      vector_push(st, 3);

      assert_that_size_t(vector_size(st) equals to 3);
      (void)vector_pop(st);
      assert_that_size_t(vector_size(st) equals to 2);
      (void)vector_pop(st);
      assert_that_size_t(vector_size(st) equals to 1);
      (void)vector_pop(st);
      assert_that_size_t(vector_size(st) equals to 0);
      (void)vector_pop(st);
      assert_that_size_t(vector_size(st) equals to 0);
      (void)vector_pop(st);
      assert_that_size_t(vector_size(st) equals to 0);

      vector_free(st);
    });

    after({ vector_free(st); });
  });
})

#endif
