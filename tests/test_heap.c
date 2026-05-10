/**
 * @file test_heap.c
 */

#include "../data_structures/heap/heap.h"
#include "test.h"

TEST_CASE(heap_create_destroy) {
  heap_t *h = heap_create();
  ASSERT_NOT_NULL(h);
  ASSERT_TRUE(heap_is_empty(h));
  heap_destroy(h);
}

TEST_CASE(heap_min_priority_order) {
  heap_t *h = heap_create();
  int input[] = {5, 1, 9, 3, 7, 2, 8, 4, 6};
  for (size_t i = 0; i < sizeof(input) / sizeof(int); i++) {
    ASSERT_TRUE(heap_insert(h, input[i]));
  }
  ASSERT_EQ_SIZE(heap_size(h), 9);

  /* Extracting from a min-heap yields ascending order. */
  for (int expected = 1; expected <= 9; expected++) {
    int v;
    ASSERT_TRUE(heap_extract_min(h, &v));
    ASSERT_EQ_INT(v, expected);
  }
  ASSERT_TRUE(heap_is_empty(h));
  heap_destroy(h);
}

TEST_CASE(heap_peek_doesnt_pop) {
  heap_t *h = heap_create();
  heap_insert(h, 42);
  int v;
  ASSERT_TRUE(heap_peek_min(h, &v));
  ASSERT_EQ_INT(v, 42);
  ASSERT_EQ_SIZE(heap_size(h), 1);
  heap_destroy(h);
}

TEST_CASE(heap_extract_empty_fails) {
  heap_t *h = heap_create();
  int v;
  ASSERT_FALSE(heap_extract_min(h, &v));
  ASSERT_FALSE(heap_peek_min(h, &v));
  heap_destroy(h);
}

TEST_CASE(heap_build_in_place_linear) {
  int arr[] = {5, 1, 9, 3, 7, 2, 8, 4, 6};
  size_t n = sizeof(arr) / sizeof(int);
  heap_build_min(arr, n);

  /* After build, arr[0] is the minimum. */
  ASSERT_EQ_INT(arr[0], 1);
}

void run_heap_tests(void) {
  RUN_TEST(heap_create_destroy);
  RUN_TEST(heap_min_priority_order);
  RUN_TEST(heap_peek_doesnt_pop);
  RUN_TEST(heap_extract_empty_fails);
  RUN_TEST(heap_build_in_place_linear);
}
