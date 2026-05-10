/**
 * @file test.h
 * @brief Hand-rolled assertion macros — no external dependencies.
 *
 * Failing assertions don't abort: they print a one-line failure and
 * continue, so a single `make test` run reports every failure across
 * every suite. Counts live in two ints defined in `test_runner.c`.
 */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

extern int g_test_total;
extern int g_test_failed;

#define ASSERT(cond) do {                                                 \
  g_test_total++;                                                         \
  if (!(cond)) {                                                          \
    g_test_failed++;                                                      \
    fprintf(stderr, "    ✗ %s:%d  ASSERT(%s)\n",                          \
            __FILE__, __LINE__, #cond);                                   \
  }                                                                       \
} while (0)

#define ASSERT_EQ_INT(a, b) do {                                          \
  g_test_total++;                                                         \
  long _a = (long)(a), _b = (long)(b);                                    \
  if (_a != _b) {                                                         \
    g_test_failed++;                                                      \
    fprintf(stderr, "    ✗ %s:%d  %s == %ld, expected %ld\n",             \
            __FILE__, __LINE__, #a, _a, _b);                              \
  }                                                                       \
} while (0)

#define ASSERT_EQ_STR(a, b) do {                                          \
  g_test_total++;                                                         \
  const char *_a = (a), *_b = (b);                                        \
  if (strcmp(_a, _b) != 0) {                                              \
    g_test_failed++;                                                      \
    fprintf(stderr, "    ✗ %s:%d  %s = \"%s\", expected \"%s\"\n",        \
            __FILE__, __LINE__, #a, _a, _b);                              \
  }                                                                       \
} while (0)

#define ASSERT_EQ_SIZE(a, b) ASSERT_EQ_INT((long)(a), (long)(b))

#define ASSERT_TRUE(cond)  ASSERT(cond)
#define ASSERT_FALSE(cond) ASSERT(!(cond))
#define ASSERT_NULL(p)     ASSERT((p) == NULL)
#define ASSERT_NOT_NULL(p) ASSERT((p) != NULL)

#define TEST_CASE(name) static void test_##name(void)

#define RUN_TEST(name) do {                                               \
  int failed_before = g_test_failed;                                      \
  printf("    • %s ", #name);                                             \
  test_##name();                                                          \
  printf("%s\n", g_test_failed == failed_before ? "✓" : "✗");             \
} while (0)

#endif /* TEST_H */
