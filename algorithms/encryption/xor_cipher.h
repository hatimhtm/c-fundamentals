/**
 * @file xor_cipher.h
 * @brief XOR stream cipher — repeating key.
 *
 * The same function encrypts and decrypts (XOR is its own inverse).
 * NOT cryptographically secure on its own — included as a teaching
 * primitive and a building block for one-time-pad demonstrations.
 */

#ifndef XOR_CIPHER_H
#define XOR_CIPHER_H

#include <stddef.h>

/** XOR each byte of `text[0..len)` with the cyclic key. */
void xor_apply(unsigned char *text, size_t len,
               const unsigned char *key, size_t keylen);

#endif /* XOR_CIPHER_H */
