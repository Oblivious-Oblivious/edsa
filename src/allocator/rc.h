#ifndef __EDSA_ALLOCATOR_RC_H_
#define __EDSA_ALLOCATOR_RC_H_

#include <stddef.h> /* ptrdiff_t */

/**
 * @brief A reference counted object.
 * @param count the reference count of the object.
 * @param free a function pointer to deallocate the object.
 */
typedef struct AllocatorRc {
  ptrdiff_t count;
  void (*free)(void *);
} AllocatorRc;

/**
 * @brief initializes a reference counted object.
 * @param counted the reference counted object to initialize.
 * @param free a function pointer to deallocate the object.
 */
void allocator_rc_alloc(AllocatorRc *counted, void (*free)(void *));

/**
 * @brief increments the reference count of the object.
 * @param counted the reference counted object.
 */
void allocator_rc_use(AllocatorRc *counted);

/**
 * @brief if ref_counted->count is 0 after decrementing it, frees the object.
 * @param obj the object pointer to release.
 * @param counted the reference counted object.
 */
#define allocator_rc_release(obj, counted) \
  _allocator_rc_release((void **)&(obj), counted)
void _allocator_rc_release(void **obj_vp, AllocatorRc *counted);

#endif
