/**
 * @file stack.c
 */

#include "stack.h"
#include <stdlib.h>

#define CF_STACK_INITIAL_CAP 16

struct cf_stack {
  int *data;
  size_t size;
  size_t capacity;
};

cf_stack_t *cf_stack_create(void) {
  cf_stack_t *s = malloc(sizeof(*s));
  if (!s) return NULL;
  s->data = malloc(CF_STACK_INITIAL_CAP * sizeof(int));
  if (!s->data) { free(s); return NULL; }
  s->size = 0;
  s->capacity = CF_STACK_INITIAL_CAP;
  return s;
}

void cf_stack_destroy(cf_stack_t *s) {
  if (!s) return;
  free(s->data);
  free(s);
}

bool cf_stack_push(cf_stack_t *s, int value) {
  if (!s) return false;
  if (s->size == s->capacity) {
    size_t new_cap = s->capacity * 2;
    int *grown = realloc(s->data, new_cap * sizeof(int));
    if (!grown) return false;
    s->data = grown;
    s->capacity = new_cap;
  }
  s->data[s->size++] = value;
  return true;
}

bool cf_stack_pop(cf_stack_t *s, int *out_value) {
  if (!s || s->size == 0) return false;
  s->size--;
  if (out_value) *out_value = s->data[s->size];
  return true;
}

bool cf_stack_peek(const cf_stack_t *s, int *out_value) {
  if (!s || s->size == 0) return false;
  if (out_value) *out_value = s->data[s->size - 1];
  return true;
}

size_t cf_stack_size(const cf_stack_t *s) { return s ? s->size : 0; }
bool cf_stack_is_empty(const cf_stack_t *s) { return !s || s->size == 0; }
