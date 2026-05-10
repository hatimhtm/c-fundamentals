/**
 * @file test_caesar.c
 */

#include "../algorithms/encryption/caesar.h"
#include "test.h"
#include <string.h>

TEST_CASE(caesar_encrypt_basic) {
  char text[] = "Hello World";
  caesar_encrypt(text, 3);
  ASSERT_EQ_STR(text, "Khoor Zruog");
}

TEST_CASE(caesar_decrypt_basic) {
  char text[] = "Khoor Zruog";
  caesar_decrypt(text, 3);
  ASSERT_EQ_STR(text, "Hello World");
}

TEST_CASE(caesar_negative_shift_normalises) {
  char text[] = "abc";
  caesar_encrypt(text, -1);
  ASSERT_EQ_STR(text, "zab");
}

TEST_CASE(caesar_large_shift_normalises) {
  char text[] = "abc";
  caesar_encrypt(text, 26 + 3);
  ASSERT_EQ_STR(text, "def");
}

TEST_CASE(caesar_preserves_punctuation) {
  char text[] = "Hi, World!";
  caesar_encrypt(text, 5);
  ASSERT_EQ_STR(text, "Mn, Btwqi!");
}

TEST_CASE(caesar_round_trip_random_shifts) {
  for (int s = 1; s < 26; s++) {
    char text[64];
    strcpy(text, "the quick brown fox");
    caesar_encrypt(text, s);
    caesar_decrypt(text, s);
    ASSERT_EQ_STR(text, "the quick brown fox");
  }
}

TEST_CASE(caesar_crack_recovers_shift) {
  /* Long enough English plaintext that frequency analysis converges. */
  char plain[]  = "this is a longer piece of english text that contains "
                  "enough letters for the chi squared statistic to settle "
                  "on the correct shift value reliably across many trials";
  char cipher[256];
  strcpy(cipher, plain);
  caesar_encrypt(cipher, 7);
  int guessed = caesar_crack(cipher);
  ASSERT_EQ_INT(guessed, 7);
}

void run_caesar_tests(void) {
  RUN_TEST(caesar_encrypt_basic);
  RUN_TEST(caesar_decrypt_basic);
  RUN_TEST(caesar_negative_shift_normalises);
  RUN_TEST(caesar_large_shift_normalises);
  RUN_TEST(caesar_preserves_punctuation);
  RUN_TEST(caesar_round_trip_random_shifts);
  RUN_TEST(caesar_crack_recovers_shift);
}
