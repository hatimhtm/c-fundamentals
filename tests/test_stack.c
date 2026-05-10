/**
 * @file test_stack.c
 */

#include "../data_structures/stack/stack.h"
#include "test.h"

TEST_CASE(stack_create_destroy) {
  cf_stack_t *s = cf_stack_create();
  ASSERT_NOT_NULL(s);
  ASSERT_TRUE(cf_stack_is_empty(s));
  ASSERT_EQ_SIZE(cf_stack_size(s), 0);
  cf_stack_destroy(s);
}

TEST_CASE(stack_push_pop_lifo) {
  cf_stack_t *s = cf_stack_create();
  cf_stack_push(s, 1);
  cf_stack_push(s, 2);
  cf_stack_push(s, 3);
  ASSERT_EQ_SIZE(cf_stack_size(s), 3);

  int v;
  cf_stack_pop(s, &v); ASSERT_EQ_INT(v, 3);
  cf_stack_pop(s, &v); ASSERT_EQ_INT(v, 2);
  cf_stack_pop(s, &v); ASSERT_EQ_INT(v, 1);
  ASSERT_TRUE(cf_stack_is_empty(s));
  cf_stack_destroy(s);
}

TEST_CASE(stack_peek) {
  cf_stack_t *s = cf_stack_create();
  cf_stack_push(s, 42);
  int v;
  ASSERT_TRUE(cf_stack_peek(s, &v));
  ASSERT_EQ_INT(v, 42);
  ASSERT_EQ_SIZE(cf_stack_size(s), 1); /* peek doesn't pop */
  cf_stack_destroy(s);
}

TEST_CASE(stack_pop_empty_fails) {
  cf_stack_t *s = cf_stack_create();
  int v = -1;
  ASSERT_FALSE(cf_stack_pop(s, &v));
  cf_stack_destroy(s);
}

TEST_CASE(stack_resize_under_pressure) {
  cf_stack_t *s = cf_stack_create();
  for (int i = 0; i < 100; i++) ASSERT_TRUE(cf_stack_push(s, i));
  ASSERT_EQ_SIZE(cf_stack_size(s), 100);
  for (int i = 99; i >= 0; i--) {
    int v;
    ASSERT_TRUE(cf_stack_pop(s, &v));
    ASSERT_EQ_INT(v, i);
  }
  cf_stack_destroy(s);
}

void run_stack_tests(void) {
  RUN_TEST(stack_create_destroy);
  RUN_TEST(stack_push_pop_lifo);
  RUN_TEST(stack_peek);
  RUN_TEST(stack_pop_empty_fails);
  RUN_TEST(stack_resize_under_pressure);
}
