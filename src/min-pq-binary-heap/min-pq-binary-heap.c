#include "min-pq-binary-heap.h"

/**
 * @brief Swaps the values on 2 specified indices
 * @param a -> The first index
 * @param b -> The first index
 */
static void pq_swap_values(void **a, void **b) {
  void *t;
  t  = *a;
  *a = *b;
  *b = t;
}

/**
 * @brief Get the right child of a node of a tree
 * @param self -> The PQ object
 * @param index -> The index whose child we look for
 * @return size_t -> The right child index
 */
static size_t get_right_child(EdsaMinPQBinaryHeap *self, size_t index) {
  if((((2 * index) + 1) < self->max_size) && (index >= 1)) {
    return (2 * index) + 1;
  }
  return -1;
}

/**
 * @brief Get the left child of a node of a tree
 * @param self -> The PQ object
 * @param index -> The index whose child we look for
 * @return size_t -> The left child index
 */
static size_t get_left_child(EdsaMinPQBinaryHeap *self, size_t index) {
  if(((2 * index) < self->max_size) && (index >= 1)) {
    return 2 * index;
  }
  return -1;
}

/**
 * @brief Get the parent of a node of a tree
 * @param self -> The PQ object
 * @param index -> The index whose parent we look for
 * @return size_t -> The parent index
 */
static size_t get_parent(EdsaMinPQBinaryHeap *self, size_t index) {
  if((index > 1) && (index < self->max_size)) {
    return index / 2;
  }
  return -1;
}

static void pq_min_heapify(EdsaMinPQBinaryHeap *self, size_t index) {
  size_t left_child_index  = get_left_child(self, index);
  size_t right_child_index = get_right_child(self, index);

  /* finding smallest among index, left child and right child */
  size_t smallest = index;

  if((left_child_index <= self->size) && (left_child_index > 0)) {
    if(self->A[left_child_index] < self->A[smallest]) {
      smallest = left_child_index;
    }
  }

  if((right_child_index <= self->size && (right_child_index > 0))) {
    if(self->A[right_child_index] < self->A[smallest]) {
      smallest = right_child_index;
    }
  }

  /* smallest is not the node, node is not a heap */
  if(smallest != index) {
    pq_swap_values(&self->A[index], &self->A[smallest]);
    pq_min_heapify(self, smallest);
  }
}

EdsaMinPQBinaryHeap *pq_new(size_t max_size) {
  EdsaMinPQBinaryHeap *self =
    (EdsaMinPQBinaryHeap *)malloc(sizeof(EdsaMinPQBinaryHeap));
  self->max_size = max_size;
  self->size     = 0;
  self->A        = (void **)malloc(sizeof(void *) * self->max_size);

  return self;
}

bool pq_is_empty(EdsaMinPQBinaryHeap *self) { return self->size == 0; }

void *pq_get_min(EdsaMinPQBinaryHeap *self) { return self->A[1]; }

void *pq_delete_min(EdsaMinPQBinaryHeap *self) {
  void *minm = self->A[1];
  self->A[1] = self->A[self->size];
  self->size--;
  pq_min_heapify(self, 1);
  return minm;
}

void pq_fix_up(EdsaMinPQBinaryHeap *self, size_t index, void *key) {
  self->A[index] = key;
  while((index > 1) && (self->A[get_parent(self, index)] > self->A[index])) {
    pq_swap_values(&self->A[index], &self->A[get_parent(self, index)]);
    index = get_parent(self, index);
  }
}

void pq_fix_down(EdsaMinPQBinaryHeap *self, size_t index, void *key) {
  self->A[index] = key;
  pq_min_heapify(self, index);
}

void pq_insert(EdsaMinPQBinaryHeap *self, void *key) {
  self->size++;
  self->A[self->size] = NULL;
  pq_fix_up(self, self->size, key);
}

void pq_print(EdsaMinPQBinaryHeap *self) {
  size_t i;
  for(i = 1; i <= self->size; i++) {
    printf("%ld\n", (long)self->A[i]);
  }
  printf("\n");
}

void pq_reset(EdsaMinPQBinaryHeap *self) {
  pq_free(self);
  self = pq_new(self->size);
}

void pq_free(EdsaMinPQBinaryHeap *self) {
  /* TODO -> GIVE A FUNCTION FOR CUSTOM ELEMENTS */

  free(self->A);
  free(self);
}
