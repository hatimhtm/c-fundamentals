/**
 * @file test_vigenere.c
 */

#include "../algorithms/encryption/vigenere.h"
#include "test.h"
#include <string.h>

TEST_CASE(vigenere_textbook) {
  /* Classic example: "attackatdawn" + key "lemon" → "lxfopvefrnhr". */
  char text[] = "attackatdawn";
  vigenere_encrypt(text, "LEMON");
  ASSERT_EQ_STR(text, "lxfopvefrnhr");
}

TEST_CASE(vigenere_case_preserved) {
  char text[] = "Attack At Dawn";
  vigenere_encrypt(text, "lemon");
  /* Spaces preserved, case preserved, key cycles only across letters. */
  ASSERT_EQ_STR(text, "Lxfopv Ef Rnhr");
}

TEST_CASE(vigenere_round_trip) {
  char text[64];
  strcpy(text, "the quick brown fox jumps over the lazy dog");
  vigenere_encrypt(text, "secret");
  vigenere_decrypt(text, "secret");
  ASSERT_EQ_STR(text, "the quick brown fox jumps over the lazy dog");
}

TEST_CASE(vigenere_empty_key_noop) {
  char text[] = "hello";
  vigenere_encrypt(text, "");
  ASSERT_EQ_STR(text, "hello");
}

TEST_CASE(vigenere_punctuation_passthrough) {
  char text[] = "Hello, World!";
  vigenere_encrypt(text, "ab");
  /* 'a' shift = 0 (no change), 'b' shift = 1 */
  /* H(a=0)=H, e(b=1)=f, l(a=0)=l, l(b=1)=m, o(a=0)=o → comma skipped, ' ' skipped, W(b=1)=X, etc */
  vigenere_decrypt(text, "ab");
  ASSERT_EQ_STR(text, "Hello, World!"); /* round-trip */
}

void run_vigenere_tests(void) {
  RUN_TEST(vigenere_textbook);
  RUN_TEST(vigenere_case_preserved);
  RUN_TEST(vigenere_round_trip);
  RUN_TEST(vigenere_empty_key_noop);
  RUN_TEST(vigenere_punctuation_passthrough);
}
