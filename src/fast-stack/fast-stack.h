#ifndef __EDSA_FAST_STACK_H_
#define __EDSA_FAST_STACK_H_

/**
 * @brief Push an item to the top of the stack pointer and increases
 * @param sp -> The stack pointer
 * @param item -> The item to push
 */
#define fs_push(sp, item) (*(sp)++ = (item))

/**
 * @brief Pops an item from the top of the stack pointer and decreases
 * @param sp -> The stack pointer
 * @return -> The popped item
 *
 */
#define fs_pop(sp) (*--(sp))

/**
 * @brief Peeks an item from the top of the stack pointer without decreasing
 * @param sp -> The stack pointer
 * @param distance -> The distance from the top of the stack pointer
 * @return -> The peeked item
 */
#define fs_peek(sp, distance) *((sp) - 1 - (distance))

#endif
