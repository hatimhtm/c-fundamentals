/**
 * @file test_bst.c
 */

#include "../data_structures/bst/bst.h"
#include "test.h"

TEST_CASE(bst_create_destroy) {
  bst_t *t = bst_create();
  ASSERT_NOT_NULL(t);
  ASSERT_EQ_SIZE(bst_size(t), 0);
  bst_destroy(t);
}

TEST_CASE(bst_insert_contains) {
  bst_t *t = bst_create();
  bst_insert(t, 5);
  bst_insert(t, 3);
  bst_insert(t, 7);
  bst_insert(t, 1);
  bst_insert(t, 9);
  ASSERT_EQ_SIZE(bst_size(t), 5);

  ASSERT_TRUE(bst_contains(t, 5));
  ASSERT_TRUE(bst_contains(t, 1));
  ASSERT_TRUE(bst_contains(t, 9));
  ASSERT_FALSE(bst_contains(t, 4));
  ASSERT_FALSE(bst_contains(t, 100));
  bst_destroy(t);
}

TEST_CASE(bst_duplicates_ignored) {
  bst_t *t = bst_create();
  bst_insert(t, 5);
  bst_insert(t, 5);
  bst_insert(t, 5);
  ASSERT_EQ_SIZE(bst_size(t), 1);
  bst_destroy(t);
}

TEST_CASE(bst_min_max) {
  bst_t *t = bst_create();
  int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 90};
  for (size_t i = 0; i < sizeof(values) / sizeof(int); i++) {
    bst_insert(t, values[i]);
  }
  int m;
  ASSERT_TRUE(bst_min(t, &m));  ASSERT_EQ_INT(m, 10);
  ASSERT_TRUE(bst_max(t, &m));  ASSERT_EQ_INT(m, 90);
  bst_destroy(t);
}

static void collect(int v, void *ctx) {
  int *arr_and_idx = (int *)ctx;
  int idx = arr_and_idx[0];
  arr_and_idx[idx + 1] = v;
  arr_and_idx[0] = idx + 1;
}

TEST_CASE(bst_in_order_is_sorted) {
  bst_t *t = bst_create();
  int input[] = {5, 1, 9, 3, 7, 2, 8, 4, 6};
  for (size_t i = 0; i < sizeof(input) / sizeof(int); i++) {
    bst_insert(t, input[i]);
  }

  int collected[16] = {0}; /* index 0 is the cursor; values start at index 1 */
  bst_in_order(t, collect, collected);

  ASSERT_EQ_INT(collected[0], 9);
  for (int i = 0; i < 9; i++) {
    ASSERT_EQ_INT(collected[i + 1], i + 1);
  }
  bst_destroy(t);
}

TEST_CASE(bst_min_empty_fails) {
  bst_t *t = bst_create();
  int v;
  ASSERT_FALSE(bst_min(t, &v));
  ASSERT_FALSE(bst_max(t, &v));
  bst_destroy(t);
}

void run_bst_tests(void) {
  RUN_TEST(bst_create_destroy);
  RUN_TEST(bst_insert_contains);
  RUN_TEST(bst_duplicates_ignored);
  RUN_TEST(bst_min_max);
  RUN_TEST(bst_in_order_is_sorted);
  RUN_TEST(bst_min_empty_fails);
}
