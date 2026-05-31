#ifndef __EDSA_LINKED_LIST_DUP_MODULE_SPEC_H_
#define __EDSA_LINKED_LIST_DUP_MODULE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/linked-list/linked-list-dup.h"

module(T_linked_list_dup, {
  describe("linked list dup", {
    it("returns NULL when duplicating a NULL list", {
      EdsaLinkedList *dup = linked_list_dup(NULL);
      assert_that(dup is NULL);
    });

    it("duplicates an empty list", {
      EdsaLinkedList *l   = linked_list_new();
      EdsaLinkedList *dup = linked_list_dup(l);
      assert_that(dup isnot NULL);
      assert_that_size_t(dup->length equals to 0);
      assert_that(dup->head is NULL);
      linked_list_free(l);
      linked_list_free(dup);
    });

    it("duplicates a list with elements", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)10);
      linked_list_add(l, (void *)20);
      linked_list_add(l, (void *)30);
      EdsaLinkedList *dup = linked_list_dup(l);
      assert_that(dup isnot NULL);
      assert_that_size_t(dup->length equals to 3);
      assert_that(dup->head->item is(void *) 10);
      assert_that(dup->head->next->item is(void *) 20);
      assert_that(dup->head->next->next->item is(void *) 30);
      linked_list_free(l);
      linked_list_free(dup);
    });

    it("creates an independent copy", {
      EdsaLinkedList *l = linked_list_new();
      linked_list_add(l, (void *)1);
      linked_list_add(l, (void *)2);
      EdsaLinkedList *dup = linked_list_dup(l);
      linked_list_remove(l, (void *)1);
      assert_that_size_t(l->length equals to 1);
      assert_that_size_t(dup->length equals to 2);
      linked_list_free(l);
      linked_list_free(dup);
    });
  });
})

#endif
