/**
 * @file test_linked_list.c
 */

#include "../data_structures/linked_list/linked_list.h"
#include "test.h"

TEST_CASE(ll_create_destroy) {
  linked_list_t *l = ll_create();
  ASSERT_NOT_NULL(l);
  ASSERT_TRUE(ll_is_empty(l));
  ASSERT_EQ_SIZE(ll_size(l), 0);
  ll_destroy(l);
}

TEST_CASE(ll_push_front) {
  linked_list_t *l = ll_create();
  ll_push_front(l, 1);
  ll_push_front(l, 2);
  ll_push_front(l, 3);
  ASSERT_EQ_SIZE(ll_size(l), 3);
  /* head should now be 3 → 2 → 1 */
  int v;
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 3);
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 2);
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 1);
  ASSERT_TRUE(ll_is_empty(l));
  ll_destroy(l);
}

TEST_CASE(ll_push_back) {
  linked_list_t *l = ll_create();
  ll_push_back(l, 1);
  ll_push_back(l, 2);
  ll_push_back(l, 3);
  ASSERT_EQ_SIZE(ll_size(l), 3);
  int v;
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 1);
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 2);
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 3);
  ll_destroy(l);
}

TEST_CASE(ll_find) {
  linked_list_t *l = ll_create();
  ll_push_back(l, 10);
  ll_push_back(l, 20);
  ll_push_back(l, 30);
  ASSERT_EQ_SIZE(ll_find(l, 10), 0);
  ASSERT_EQ_SIZE(ll_find(l, 20), 1);
  ASSERT_EQ_SIZE(ll_find(l, 30), 2);
  ASSERT_EQ_SIZE(ll_find(l, 99), LL_NOT_FOUND);
  ll_destroy(l);
}

TEST_CASE(ll_reverse) {
  linked_list_t *l = ll_create();
  ll_push_back(l, 1);
  ll_push_back(l, 2);
  ll_push_back(l, 3);
  ll_reverse(l);
  int v;
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 3);
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 2);
  ll_pop_front(l, &v); ASSERT_EQ_INT(v, 1);
  ll_destroy(l);
}

TEST_CASE(ll_pop_empty_fails) {
  linked_list_t *l = ll_create();
  int v = -1;
  ASSERT_FALSE(ll_pop_front(l, &v));
  ll_destroy(l);
}

void run_linked_list_tests(void) {
  RUN_TEST(ll_create_destroy);
  RUN_TEST(ll_push_front);
  RUN_TEST(ll_push_back);
  RUN_TEST(ll_find);
  RUN_TEST(ll_reverse);
  RUN_TEST(ll_pop_empty_fails);
}
