/**
 * @file test_trie.c
 */

#include "../data_structures/trie/trie.h"
#include "test.h"

TEST_CASE(trie_create_destroy) {
  trie_t *t = trie_create();
  ASSERT_NOT_NULL(t);
  trie_destroy(t);
}

TEST_CASE(trie_insert_contains) {
  trie_t *t = trie_create();
  ASSERT_TRUE(trie_insert(t, "cat"));
  ASSERT_TRUE(trie_insert(t, "car"));
  ASSERT_TRUE(trie_insert(t, "cart"));
  ASSERT_TRUE(trie_insert(t, "dog"));

  ASSERT_TRUE(trie_contains(t, "cat"));
  ASSERT_TRUE(trie_contains(t, "car"));
  ASSERT_TRUE(trie_contains(t, "cart"));
  ASSERT_TRUE(trie_contains(t, "dog"));

  ASSERT_FALSE(trie_contains(t, "ca"));     /* prefix not inserted as terminal */
  ASSERT_FALSE(trie_contains(t, "cars"));
  ASSERT_FALSE(trie_contains(t, "elephant"));
  trie_destroy(t);
}

TEST_CASE(trie_starts_with) {
  trie_t *t = trie_create();
  trie_insert(t, "cat");
  trie_insert(t, "car");
  trie_insert(t, "cart");

  ASSERT_TRUE(trie_starts_with(t, "ca"));
  ASSERT_TRUE(trie_starts_with(t, "car"));
  ASSERT_TRUE(trie_starts_with(t, "cart"));
  ASSERT_TRUE(trie_starts_with(t, "")); /* empty prefix matches root */
  ASSERT_FALSE(trie_starts_with(t, "do"));
  trie_destroy(t);
}

TEST_CASE(trie_rejects_non_lowercase) {
  trie_t *t = trie_create();
  ASSERT_FALSE(trie_insert(t, "Hello"));   /* uppercase rejected */
  ASSERT_FALSE(trie_insert(t, "abc123"));  /* digits rejected */
  ASSERT_FALSE(trie_insert(t, "a-b"));     /* punctuation rejected */
  trie_destroy(t);
}

void run_trie_tests(void) {
  RUN_TEST(trie_create_destroy);
  RUN_TEST(trie_insert_contains);
  RUN_TEST(trie_starts_with);
  RUN_TEST(trie_rejects_non_lowercase);
}
