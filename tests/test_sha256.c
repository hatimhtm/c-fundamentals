/**
 * @file test_sha256.c
 *
 * Tests against canonical NIST test vectors.
 */

#include "../algorithms/encryption/sha256.h"
#include "test.h"
#include <string.h>

static void expect_sha256(const char *input, const char *expected_hex) {
  uint8_t digest[SHA256_DIGEST_BYTES];
  char hex[SHA256_HEX_BYTES];
  sha256((const uint8_t *)input, strlen(input), digest);
  sha256_to_hex(digest, hex);
  ASSERT_EQ_STR(hex, expected_hex);
}

TEST_CASE(sha256_empty_string) {
  /* SHA-256 of "" is a well-known constant. */
  expect_sha256("",
    "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

TEST_CASE(sha256_abc) {
  /* NIST FIPS 180-4 example. */
  expect_sha256("abc",
    "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
}

TEST_CASE(sha256_long_message) {
  /* NIST FIPS 180-4 example #2. 56-byte input — exercises the boundary
     between 1-block and 2-block padding. */
  expect_sha256(
    "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
    "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
}

TEST_CASE(sha256_hex_format_lowercase_64chars) {
  uint8_t digest[SHA256_DIGEST_BYTES];
  char hex[SHA256_HEX_BYTES];
  sha256((const uint8_t *)"hello", 5, digest);
  sha256_to_hex(digest, hex);

  ASSERT_EQ_INT(strlen(hex), 64);
  for (int i = 0; i < 64; i++) {
    char c = hex[i];
    ASSERT_TRUE((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'));
  }
}

void run_sha256_tests(void) {
  RUN_TEST(sha256_empty_string);
  RUN_TEST(sha256_abc);
  RUN_TEST(sha256_long_message);
  RUN_TEST(sha256_hex_format_lowercase_64chars);
}
