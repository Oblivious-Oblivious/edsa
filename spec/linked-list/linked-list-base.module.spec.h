#ifndef __EDSA_LINKED_LIST_BASE_MODULE_SPEC_H_
#define __EDSA_LINKED_LIST_BASE_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/linked-list/linked-list-base.h"

module(T_linked_list_base, {
  describe("linked list base", {
    it("creates a new empty linked list", {
      EdsaLinkedList *l = linked_list_new();
      assert_that(l isnot NULL);
      assert_that_size_t(l->length equals to 0);
      assert_that(l->head is NULL);
      linked_list_free(l);
    });

    it("adds elements to the linked list", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)1);
      linked_list_add(l, (void *)2);
      linked_list_add(l, (void *)3);
      assert_that_size_t(l->length equals to 3);
      assert_that(l->head isnot NULL);
      assert_that(l->head->item is(void *) 1);
      assert_that(l->head->next->item is(void *) 2);
      assert_that(l->head->next->next->item is(void *) 3);
      assert_that(l->head->next->next->next is NULL);
      linked_list_free(l);
    });

    it("does not add NULL items", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, NULL);
      assert_that_size_t(l->length equals to 0);
      assert_that(l->head is NULL);
      linked_list_free(l);
    });

    it("does not add to a NULL list", { linked_list_add(NULL, (void *)1); });

    it("removes an element from the linked list", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)1);
      linked_list_add(l, (void *)2);
      linked_list_add(l, (void *)3);
      linked_list_remove(l, (void *)2);
      assert_that_size_t(l->length equals to 2);
      assert_that(l->head->item is(void *) 1);
      assert_that(l->head->next->item is(void *) 3);
      linked_list_free(l);
    });

    it("removes the head element", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)1);
      linked_list_add(l, (void *)2);
      linked_list_remove(l, (void *)1);
      assert_that_size_t(l->length equals to 1);
      assert_that(l->head->item is(void *) 2);
      linked_list_free(l);
    });

    it("removes the last element", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)1);
      linked_list_add(l, (void *)2);
      linked_list_remove(l, (void *)2);
      assert_that_size_t(l->length equals to 1);
      assert_that(l->head->item is(void *) 1);
      assert_that(l->head->next is NULL);
      linked_list_free(l);
    });

    it("does nothing when removing a non-existent element", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)1);
      linked_list_remove(l, (void *)99);
      assert_that_size_t(l->length equals to 1);
      linked_list_free(l);
    });

    it("does nothing when removing from a NULL list", {
      linked_list_remove(NULL, (void *)1);
    });

    it("does nothing when removing NULL from a list", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)1);
      linked_list_remove(l, NULL);
      assert_that_size_t(l->length equals to 1);
      linked_list_free(l);
    });

    it("removes all elements leaving the list empty", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)1);
      linked_list_add(l, (void *)2);
      linked_list_remove(l, (void *)1);
      linked_list_remove(l, (void *)2);
      assert_that_size_t(l->length equals to 0);
      assert_that(l->head is NULL);
      linked_list_free(l);
    });

    it("frees a NULL list without crashing", { linked_list_free(NULL); });
  });
})

#endif
