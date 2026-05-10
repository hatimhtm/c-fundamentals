/**
 * @file test_queue.c
 */

#include "../data_structures/queue/queue.h"
#include "test.h"

TEST_CASE(queue_create_destroy) {
  queue_t *q = queue_create();
  ASSERT_NOT_NULL(q);
  ASSERT_TRUE(queue_is_empty(q));
  queue_destroy(q);
}

TEST_CASE(queue_fifo_order) {
  queue_t *q = queue_create();
  queue_enqueue(q, 1);
  queue_enqueue(q, 2);
  queue_enqueue(q, 3);
  ASSERT_EQ_SIZE(queue_size(q), 3);

  int v;
  queue_dequeue(q, &v); ASSERT_EQ_INT(v, 1);
  queue_dequeue(q, &v); ASSERT_EQ_INT(v, 2);
  queue_dequeue(q, &v); ASSERT_EQ_INT(v, 3);
  ASSERT_TRUE(queue_is_empty(q));
  queue_destroy(q);
}

TEST_CASE(queue_peek) {
  queue_t *q = queue_create();
  queue_enqueue(q, 42);
  int v;
  ASSERT_TRUE(queue_peek(q, &v));
  ASSERT_EQ_INT(v, 42);
  ASSERT_EQ_SIZE(queue_size(q), 1);
  queue_destroy(q);
}

TEST_CASE(queue_dequeue_empty_fails) {
  queue_t *q = queue_create();
  int v = -1;
  ASSERT_FALSE(queue_dequeue(q, &v));
  queue_destroy(q);
}

TEST_CASE(queue_circular_under_pressure) {
  queue_t *q = queue_create();
  /* Wraparound + resize stress. */
  for (int i = 0; i < 50; i++) ASSERT_TRUE(queue_enqueue(q, i));
  for (int i = 0; i < 25; i++) {
    int v;
    ASSERT_TRUE(queue_dequeue(q, &v));
    ASSERT_EQ_INT(v, i);
  }
  for (int i = 50; i < 100; i++) ASSERT_TRUE(queue_enqueue(q, i));
  for (int i = 25; i < 100; i++) {
    int v;
    ASSERT_TRUE(queue_dequeue(q, &v));
    ASSERT_EQ_INT(v, i);
  }
  ASSERT_TRUE(queue_is_empty(q));
  queue_destroy(q);
}

void run_queue_tests(void) {
  RUN_TEST(queue_create_destroy);
  RUN_TEST(queue_fifo_order);
  RUN_TEST(queue_peek);
  RUN_TEST(queue_dequeue_empty_fails);
  RUN_TEST(queue_circular_under_pressure);
}
