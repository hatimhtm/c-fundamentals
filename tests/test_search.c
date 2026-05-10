/**
 * @file test_search.c
 */

#include "../algorithms/searching/binary_search.h"
#include "test.h"

TEST_CASE(bsearch_finds_existing) {
  int arr[] = {1, 3, 5, 7, 9, 11, 13};
  ASSERT_EQ_SIZE(binary_search_ints(arr, 7, 7), 3);
  ASSERT_EQ_SIZE(binary_search_ints(arr, 7, 1), 0);
  ASSERT_EQ_SIZE(binary_search_ints(arr, 7, 13), 6);
}

TEST_CASE(bsearch_missing) {
  int arr[] = {1, 3, 5, 7, 9};
  ASSERT_EQ_SIZE(binary_search_ints(arr, 5, 4), BSEARCH_NOT_FOUND);
  ASSERT_EQ_SIZE(binary_search_ints(arr, 5, 100), BSEARCH_NOT_FOUND);
  ASSERT_EQ_SIZE(binary_search_ints(arr, 5, -1), BSEARCH_NOT_FOUND);
}

TEST_CASE(bsearch_empty) {
  int arr[1];
  ASSERT_EQ_SIZE(binary_search_ints(arr, 0, 5), BSEARCH_NOT_FOUND);
}

TEST_CASE(bsearch_strings) {
  const char *arr[] = {"apple", "banana", "cherry", "date", "elderberry"};
  ASSERT_EQ_SIZE(binary_search_strings(arr, 5, "cherry"), 2);
  ASSERT_EQ_SIZE(binary_search_strings(arr, 5, "banana"), 1);
  ASSERT_EQ_SIZE(binary_search_strings(arr, 5, "fig"), BSEARCH_NOT_FOUND);
}

TEST_CASE(bsearch_recursive_matches_iterative) {
  int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
  for (int t = 1; t <= 21; t++) {
    size_t i = binary_search_ints(arr, 10, t);
    size_t r = binary_search_ints_recursive(arr, 0, 9, t);
    ASSERT_EQ_SIZE(i, r);
  }
}

void run_search_tests(void) {
  RUN_TEST(bsearch_finds_existing);
  RUN_TEST(bsearch_missing);
  RUN_TEST(bsearch_empty);
  RUN_TEST(bsearch_strings);
  RUN_TEST(bsearch_recursive_matches_iterative);
}
