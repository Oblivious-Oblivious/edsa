#ifndef __EDSA_LINKED_LIST_FUNCTIONAL_FUNCTIONS_MODULE_SPEC_H_
#define __EDSA_LINKED_LIST_FUNCTIONAL_FUNCTIONS_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/linked-list/linked-list-functional-functions.h"

static void *ll_double_value(void *item) { return (void *)((long)item * 2); }

static void *ll_filter_greater_than_2(void *item) {
  return (void *)(long)((long)item > 2);
}

static void *ll_sum(void *acc, void *item) {
  return (void *)((long)acc + (long)item);
}

module(T_linked_list_functional_functions, {
  describe("linked list functional functions", {
    context("#linked_list_map", {
      it("returns NULL when mapping a NULL list", {
        EdsaLinkedList *result = linked_list_map(NULL, ll_double_value);
        assert_that(result is NULL);
      });

      it("returns NULL when modifier is NULL", {
        EdsaLinkedList *l      = linked_list_new();
        EdsaLinkedList *result = linked_list_map(l, NULL);
        assert_that(result is NULL);
        linked_list_free(l);
      });

      it("maps an empty list", {
        EdsaLinkedList *l      = linked_list_new();
        EdsaLinkedList *result = linked_list_map(l, ll_double_value);
        assert_that(result isnot NULL);
        assert_that_size_t(result->length equals to 0);
        linked_list_free(l);
        linked_list_free(result);
      });

      it("maps values to their doubles", {
        EdsaLinkedList *l = linked_list_new();
        linked_list_add(l, (void *)1);
        linked_list_add(l, (void *)2);
        linked_list_add(l, (void *)3);
        EdsaLinkedList *result = linked_list_map(l, ll_double_value);
        assert_that_size_t(result->length equals to 3);
        assert_that(result->head->item is(void *) 2);
        assert_that(result->head->next->item is(void *) 4);
        assert_that(result->head->next->next->item is(void *) 6);
        linked_list_free(l);
        linked_list_free(result);
      });
    });

    context("#linked_list_filter", {
      it("returns NULL when filtering a NULL list", {
        EdsaLinkedList *result =
          linked_list_filter(NULL, ll_filter_greater_than_2);
        assert_that(result is NULL);
      });

      it("returns NULL when filter is NULL", {
        EdsaLinkedList *l      = linked_list_new();
        EdsaLinkedList *result = linked_list_filter(l, NULL);
        assert_that(result is NULL);
        linked_list_free(l);
      });

      it("filters elements greater than 2", {
        EdsaLinkedList *l = linked_list_new();
        linked_list_add(l, (void *)1);
        linked_list_add(l, (void *)2);
        linked_list_add(l, (void *)3);
        linked_list_add(l, (void *)4);
        EdsaLinkedList *result =
          linked_list_filter(l, ll_filter_greater_than_2);
        assert_that_size_t(result->length equals to 2);
        assert_that(result->head->item is(void *) 1);
        assert_that(result->head->next->item is(void *) 2);
        linked_list_free(l);
        linked_list_free(result);
      });
    });

    context("#linked_list_reduce", {
      it("returns NULL when reducing a NULL list", {
        void *result = linked_list_reduce(NULL, ll_sum);
        assert_that(result is NULL);
      });

      it("returns NULL when fold is NULL", {
        EdsaLinkedList *l = linked_list_new();
        void *result      = linked_list_reduce(l, NULL);
        assert_that(result is NULL);
        linked_list_free(l);
      });

      it("returns NULL when reducing an empty list", {
        EdsaLinkedList *l = linked_list_new();
        void *result      = linked_list_reduce(l, ll_sum);
        assert_that(result is NULL);
        linked_list_free(l);
      });

      it("reduces a single element list", {
        EdsaLinkedList *l = linked_list_new();
        linked_list_add(l, (void *)42);
        void *result = linked_list_reduce(l, ll_sum);
        assert_that(result is(void *) 42);
        linked_list_free(l);
      });

      it("reduces to the sum of elements", {
        EdsaLinkedList *l = linked_list_new();
        linked_list_add(l, (void *)1);
        linked_list_add(l, (void *)2);
        linked_list_add(l, (void *)3);
        linked_list_add(l, (void *)4);
        void *result = linked_list_reduce(l, ll_sum);
        assert_that(result is(void *) 10);
        linked_list_free(l);
      });
    });
  });
})

#endif
