/**
 * @file test_runner.c
 * @brief Test entry point — calls every suite and reports the totals.
 */

#include "test.h"

int g_test_total = 0;
int g_test_failed = 0;

extern void run_sort_tests(void);
extern void run_search_tests(void);
extern void run_caesar_tests(void);
extern void run_vigenere_tests(void);
extern void run_linked_list_tests(void);
extern void run_hash_table_tests(void);

int main(void) {
  printf("Running test suites…\n");

  printf("\n  ── sorts ──\n");
  run_sort_tests();

  printf("\n  ── search ──\n");
  run_search_tests();

  printf("\n  ── caesar ──\n");
  run_caesar_tests();

  printf("\n  ── vigenere ──\n");
  run_vigenere_tests();

  printf("\n  ── linked_list ──\n");
  run_linked_list_tests();

  printf("\n  ── hash_table ──\n");
  run_hash_table_tests();

  printf("\n────────────────────\n");
  printf("Total assertions: %d\n", g_test_total);
  printf("Failures:         %d\n", g_test_failed);
  if (g_test_failed == 0) {
    printf("✓ All tests passed.\n");
    return 0;
  }
  printf("✗ Some tests failed.\n");
  return 1;
}
