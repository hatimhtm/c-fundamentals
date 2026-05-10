/**
 * @file test_xor.c
 */

#include "../algorithms/encryption/xor_cipher.h"
#include "test.h"
#include <string.h>

TEST_CASE(xor_round_trip) {
  unsigned char text[] = "Hello, World!";
  size_t len = sizeof(text) - 1;
  unsigned char key[] = "secret";
  size_t klen = sizeof(key) - 1;

  unsigned char copy[64];
  memcpy(copy, text, len);

  xor_apply(copy, len, key, klen);
  /* Cipher text should be different from plaintext. */
  ASSERT_TRUE(memcmp(copy, text, len) != 0);

  xor_apply(copy, len, key, klen);
  /* Second pass with the same key recovers the original. */
  ASSERT_TRUE(memcmp(copy, text, len) == 0);
}

TEST_CASE(xor_with_zero_key_does_nothing) {
  unsigned char text[] = {0x42, 0xAB, 0xCC};
  unsigned char key[]  = {0x00};
  unsigned char copy[3];
  memcpy(copy, text, 3);
  xor_apply(copy, 3, key, 1);
  ASSERT_TRUE(memcmp(copy, text, 3) == 0); /* XOR with 0 is identity */
}

TEST_CASE(xor_handles_empty_key_gracefully) {
  unsigned char text[] = "abc";
  unsigned char copy[4];
  memcpy(copy, text, 4);
  xor_apply(copy, 3, (const unsigned char *)"", 0);
  /* Empty key returns early — text unchanged. */
  ASSERT_TRUE(memcmp(copy, text, 4) == 0);
}

void run_xor_tests(void) {
  RUN_TEST(xor_round_trip);
  RUN_TEST(xor_with_zero_key_does_nothing);
  RUN_TEST(xor_handles_empty_key_gracefully);
}
