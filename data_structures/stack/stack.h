/**
 * @file stack.h
 * @brief LIFO stack of `int`, backed by a growable dynamic array.
 *
 * Resize policy: doubles when full, never shrinks. push/pop/peek are
 * O(1) amortised; size and is_empty are O(1).
 *
 * Note: type is named `cf_stack_t` (rather than `stack_t`) to avoid
 * collision with POSIX `stack_t` from `<signal.h>` / `<sys/_types.h>`,
 * which is dragged in transitively by stdlib.h on macOS.
 */

#ifndef CF_STACK_H
#define CF_STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct cf_stack cf_stack_t;

cf_stack_t *cf_stack_create(void);
void cf_stack_destroy(cf_stack_t *s);

bool cf_stack_push(cf_stack_t *s, int value);
bool cf_stack_pop(cf_stack_t *s, int *out_value);
bool cf_stack_peek(const cf_stack_t *s, int *out_value);

size_t cf_stack_size(const cf_stack_t *s);
bool cf_stack_is_empty(const cf_stack_t *s);

#endif /* CF_STACK_H */
