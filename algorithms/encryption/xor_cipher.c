/**
 * @file xor_cipher.c
 */

#include "xor_cipher.h"

void xor_apply(unsigned char *text, size_t len,
               const unsigned char *key, size_t keylen) {
  if (!text || !key || keylen == 0) return;
  for (size_t i = 0; i < len; i++) {
    text[i] ^= key[i % keylen];
  }
}
