/**
 * @file test_hash_table.c
 */

#include "../data_structures/hash_table/hash_table.h"
#include "test.h"
#include <stdio.h>

TEST_CASE(ht_create_destroy) {
  hash_table_t *ht = ht_create();
  ASSERT_NOT_NULL(ht);
  ASSERT_EQ_SIZE(ht_size(ht), 0);
  ASSERT_TRUE(ht_capacity(ht) > 0);
  ht_destroy(ht);
}

TEST_CASE(ht_set_get) {
  hash_table_t *ht = ht_create();
  ASSERT_TRUE(ht_set(ht, "alice", 1));
  ASSERT_TRUE(ht_set(ht, "bob", 2));
  ASSERT_TRUE(ht_set(ht, "carol", 3));

  int v;
  ASSERT_TRUE(ht_get(ht, "alice", &v));  ASSERT_EQ_INT(v, 1);
  ASSERT_TRUE(ht_get(ht, "bob", &v));    ASSERT_EQ_INT(v, 2);
  ASSERT_TRUE(ht_get(ht, "carol", &v));  ASSERT_EQ_INT(v, 3);
  ASSERT_FALSE(ht_get(ht, "dave", &v));
  ht_destroy(ht);
}

TEST_CASE(ht_overwrite) {
  hash_table_t *ht = ht_create();
  ht_set(ht, "k", 1);
  ht_set(ht, "k", 99);
  int v;
  ASSERT_TRUE(ht_get(ht, "k", &v));
  ASSERT_EQ_INT(v, 99);
  ASSERT_EQ_SIZE(ht_size(ht), 1);
  ht_destroy(ht);
}

TEST_CASE(ht_remove) {
  hash_table_t *ht = ht_create();
  ht_set(ht, "alice", 1);
  ht_set(ht, "bob", 2);
  ASSERT_TRUE(ht_remove(ht, "alice"));
  ASSERT_FALSE(ht_contains(ht, "alice"));
  ASSERT_TRUE(ht_contains(ht, "bob"));
  ASSERT_EQ_SIZE(ht_size(ht), 1);
  ASSERT_FALSE(ht_remove(ht, "alice")); /* second remove fails */
  ht_destroy(ht);
}

TEST_CASE(ht_resize) {
  hash_table_t *ht = ht_create();
  size_t initial_cap = ht_capacity(ht);
  /* Insert enough keys to force at least one resize. */
  for (int i = 0; i < 50; i++) {
    char key[16];
    snprintf(key, sizeof(key), "key-%d", i);
    ht_set(ht, key, i);
  }
  ASSERT_TRUE(ht_capacity(ht) > initial_cap);
  ASSERT_EQ_SIZE(ht_size(ht), 50);

  /* All values still readable after rehash. */
  for (int i = 0; i < 50; i++) {
    char key[16];
    snprintf(key, sizeof(key), "key-%d", i);
    int v;
    ASSERT_TRUE(ht_get(ht, key, &v));
    ASSERT_EQ_INT(v, i);
  }
  ht_destroy(ht);
}

TEST_CASE(ht_remove_then_set_reuses_slot) {
  hash_table_t *ht = ht_create();
  ht_set(ht, "k", 1);
  ht_remove(ht, "k");
  ASSERT_TRUE(ht_set(ht, "k", 2));
  int v;
  ASSERT_TRUE(ht_get(ht, "k", &v));
  ASSERT_EQ_INT(v, 2);
  ht_destroy(ht);
}

void run_hash_table_tests(void) {
  RUN_TEST(ht_create_destroy);
  RUN_TEST(ht_set_get);
  RUN_TEST(ht_overwrite);
  RUN_TEST(ht_remove);
  RUN_TEST(ht_resize);
  RUN_TEST(ht_remove_then_set_reuses_slot);
}
