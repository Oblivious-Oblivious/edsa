#include "rc.h"

#include <stdlib.h> /* NULL */

void allocator_rc_alloc(AllocatorRc *counted, void (*free)(void *)) {
  counted->count = 0;
  counted->free  = free;
}

void allocator_rc_use(AllocatorRc *counted) { counted->count++; }

void _allocator_rc_release(void **obj_vp, AllocatorRc *counted) {
  void *to_free = *obj_vp;

  counted->count--;

  if(counted->count == 0) {
    *obj_vp = NULL;
    counted->free(to_free);
  }
}
