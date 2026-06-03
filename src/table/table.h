#ifndef __EDSA_TABLE_H_
#define __EDSA_TABLE_H_

#include "../allocator/allocator.h"
#include "../boolean/boolean.h"
#include "../hash/komihash/komihash.h"
#include "../vector/vector.h"

#define TABLE_STATE_EMPTY   (0)
#define TABLE_STATE_FILLED  (1)
#define TABLE_STATE_DELETED (2)

#define TABLE_GROW_FACTOR (2)

/** @brief Can dynamically redefine those constants Since values are integers,
 * NULL is not allowed and we define a NaN boxed undefined value */
#ifndef TABLE_UNDEFINED
  #define TABLE_UNDEFINED 0xfffc000000000000
#endif

#ifndef TABLE_LOAD_FACTOR
  #define TABLE_LOAD_FACTOR 0.78
#endif

#ifndef TABLE_INITIAL_SIZE
  #define TABLE_INITIAL_SIZE (1 << 10)
#endif

#ifndef TABLE_HASH_FUNCTION
  #define TABLE_HASH_FUNCTION hash_komihash
#endif

/**
 * @brief Data oriented table with open addressing and linear probing
 * @param keys -> The keys of the hash table
 * @param values -> The values of the hash table
 * @param hashes -> The hash values of the keys
 * @param states -> The state of each bucket (empty or filled)
 * @param size -> The number of elements in the hash table
 * @param tombstones -> The number of tombstones in the hash table
 * @param allocator -> The allocator instance (NULL for default realloc/free)
 * @param alloc_fn -> The allocator's alloc function (NULL for default realloc)
 * @param free_fn -> The table item free function (NULL for default free)
 */
typedef struct EdsaTable {
  const char **keys;
  size_t *values;
  size_t *hashes;
  uint8_t *states;
  size_t size;
  size_t tombstones;
  void *allocator;
  allocator_alloc_fn alloc_fn;
  allocator_free_fn free_fn;
} EdsaTable;

/**
 * @brief Initializes the hash table
 * @param self
 */
void table_init(EdsaTable *self);

/**
 * @brief Makes a table allocator-aware. Must be called after table_init.
 * @param self -> The hash table
 * @param allocator_ctx -> The allocator instance (or NULL)
 * @param alloc_fn -> The allocator's alloc function (or NULL for default
 * realloc)
 * @param free_fn -> The table item free function, or NULL when not needed
 */
void table_set_allocator(
  EdsaTable *self,
  void *allocator_ctx,
  allocator_alloc_fn alloc_fn,
  allocator_free_fn free_fn
);

/**
 * @brief Inserts a key-value pair into the hash table (open addressing)
 * @param self -> The hash table
 * @param key -> The key
 * @param value -> The value
 */
void table_add(EdsaTable *self, const char *key, size_t value);

/**
 * @brief Adds all entries from src to dest
 * @param src -> Initial table
 * @param dest -> New table
 */
void table_add_all(EdsaTable *src, EdsaTable *dst);

/**
 * @brief Adds all entries from src to dst except for values starting with `@::`
 * @param src -> Initial table
 * @param dst -> New table
 */
void table_add_all_non_labels(EdsaTable *src, EdsaTable *dst);

/**
 * @brief Linear probing lookup
 * @param self -> The hash table
 * @param key -> The key
 * @return size_t -> Either the value found or 0xfffc000000000000 if not found
 */
size_t table_get(EdsaTable *self, const char *key);

/**
 * @brief Removes a key-value pair from the hash table
 * @param self -> The hash table
 * @param key -> The key
 */
void table_remove(EdsaTable *self, const char *key);

/**
 * @brief Returns the size of the hash table
 * @param self -> The hash table
 * @return size_t -> The size of the hash table
 */
size_t table_size(EdsaTable *self);

/**
 * @brief Deallocates all vectors (hashtable exists on stack)
 * @param self -> The hash table
 */
void table_deinit(EdsaTable *self);

#endif
