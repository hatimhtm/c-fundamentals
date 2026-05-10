/**
 * @file sha256.h
 * @brief Pure-C SHA-256 implementation, written from the FIPS 180-4 spec.
 *
 * Operates on raw bytes; outputs the 32-byte digest. A convenience helper
 * formats the digest as a 64-char lowercase hex string. No dependencies
 * outside libc.
 */

#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>
#include <stdint.h>

#define SHA256_DIGEST_BYTES   32
#define SHA256_HEX_BYTES      (SHA256_DIGEST_BYTES * 2 + 1) /* +1 for NUL */

/** Compute SHA-256(data[0..len)) into the 32-byte `digest` buffer. */
void sha256(const uint8_t *data, size_t len, uint8_t digest[SHA256_DIGEST_BYTES]);

/** Format a 32-byte digest as a 64-char lowercase hex string + NUL. */
void sha256_to_hex(const uint8_t digest[SHA256_DIGEST_BYTES],
                   char hex_out[SHA256_HEX_BYTES]);

#endif /* SHA256_H */
