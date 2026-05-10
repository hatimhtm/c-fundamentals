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
extern void run_xor_tests(void);
extern void run_sha256_tests(void);
extern void run_linked_list_tests(void);
extern void run_hash_table_tests(void);
extern void run_stack_tests(void);
extern void run_queue_tests(void);
extern void run_bst_tests(void);
extern void run_heap_tests(void);
extern void run_trie_tests(void);

int main(void) {
  printf("Running test suites…\n");

  printf("\n  ── sorts ──\n");          run_sort_tests();
  printf("\n  ── search ──\n");         run_search_tests();
  printf("\n  ── caesar ──\n");         run_caesar_tests();
  printf("\n  ── vigenere ──\n");       run_vigenere_tests();
  printf("\n  ── xor ──\n");            run_xor_tests();
  printf("\n  ── sha256 ──\n");         run_sha256_tests();
  printf("\n  ── linked_list ──\n");    run_linked_list_tests();
  printf("\n  ── stack ──\n");          run_stack_tests();
  printf("\n  ── queue ──\n");          run_queue_tests();
  printf("\n  ── bst ──\n");            run_bst_tests();
  printf("\n  ── heap ──\n");           run_heap_tests();
  printf("\n  ── trie ──\n");           run_trie_tests();
  printf("\n  ── hash_table ──\n");     run_hash_table_tests();

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
