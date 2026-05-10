/**
 * @file sha256.c
 * @brief SHA-256 implementation per FIPS 180-4.
 *
 * Single-shot interface only — given the bytes, returns the digest.
 * The 32-bit constants K[0..63] are the first 32 bits of the fractional
 * parts of the cube roots of the first 64 primes; H0[0..7] are the same
 * for the square roots of the first 8 primes.
 */

#include "sha256.h"
#include <string.h>

static const uint32_t K[64] = {
  0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u, 0x3956c25bu, 0x59f111f1u,
  0x923f82a4u, 0xab1c5ed5u, 0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u,
  0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u, 0xe49b69c1u, 0xefbe4786u,
  0x0fc19dc6u, 0x240ca1ccu, 0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
  0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u, 0xc6e00bf3u, 0xd5a79147u,
  0x06ca6351u, 0x14292967u, 0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u,
  0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u, 0xa2bfe8a1u, 0xa81a664bu,
  0xc24b8b70u, 0xc76c51a3u, 0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
  0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u, 0x391c0cb3u, 0x4ed8aa4au,
  0x5b9cca4fu, 0x682e6ff3u, 0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u,
  0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u
};

static uint32_t rotr(uint32_t x, unsigned n) { return (x >> n) | (x << (32 - n)); }

static void process_block(uint32_t H[8], const uint8_t block[64]) {
  uint32_t W[64];

  /* Big-endian 32-bit load for each 4-byte chunk. */
  for (int i = 0; i < 16; i++) {
    W[i] = ((uint32_t)block[i * 4 + 0] << 24)
         | ((uint32_t)block[i * 4 + 1] << 16)
         | ((uint32_t)block[i * 4 + 2] <<  8)
         |  (uint32_t)block[i * 4 + 3];
  }
  for (int i = 16; i < 64; i++) {
    uint32_t s0 = rotr(W[i - 15], 7)  ^ rotr(W[i - 15], 18) ^ (W[i - 15] >> 3);
    uint32_t s1 = rotr(W[i -  2], 17) ^ rotr(W[i -  2], 19) ^ (W[i -  2] >> 10);
    W[i] = W[i - 16] + s0 + W[i - 7] + s1;
  }

  uint32_t a = H[0], b = H[1], c = H[2], d = H[3];
  uint32_t e = H[4], f = H[5], g = H[6], h = H[7];

  for (int i = 0; i < 64; i++) {
    uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
    uint32_t ch = (e & f) ^ ((~e) & g);
    uint32_t t1 = h + S1 + ch + K[i] + W[i];
    uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
    uint32_t mj = (a & b) ^ (a & c) ^ (b & c);
    uint32_t t2 = S0 + mj;
    h = g; g = f; f = e;
    e = d + t1;
    d = c; c = b; b = a;
    a = t1 + t2;
  }

  H[0] += a; H[1] += b; H[2] += c; H[3] += d;
  H[4] += e; H[5] += f; H[6] += g; H[7] += h;
}

void sha256(const uint8_t *data, size_t len, uint8_t digest[SHA256_DIGEST_BYTES]) {
  uint32_t H[8] = {
    0x6a09e667u, 0xbb67ae85u, 0x3c6ef372u, 0xa54ff53au,
    0x510e527fu, 0x9b05688cu, 0x1f83d9abu, 0x5be0cd19u
  };

  uint64_t bit_len = (uint64_t)len * 8;

  /* Process all complete 64-byte blocks. */
  size_t off = 0;
  while (len - off >= 64) {
    process_block(H, data + off);
    off += 64;
  }

  /* Last block(s): copy remainder, append 0x80, then zero-pad to 56,
     then 8-byte big-endian message length. May spill into a second block. */
  uint8_t pad[128] = {0};
  size_t rem = len - off;
  memcpy(pad, data + off, rem);
  pad[rem] = 0x80;

  size_t pad_len;
  if (rem < 56) {
    pad_len = 64;
  } else {
    pad_len = 128;
  }

  /* Big-endian length in the last 8 bytes. */
  for (int i = 0; i < 8; i++) {
    pad[pad_len - 1 - i] = (uint8_t)(bit_len >> (i * 8));
  }

  process_block(H, pad);
  if (pad_len == 128) process_block(H, pad + 64);

  /* Big-endian 32-bit store. */
  for (int i = 0; i < 8; i++) {
    digest[i * 4 + 0] = (uint8_t)(H[i] >> 24);
    digest[i * 4 + 1] = (uint8_t)(H[i] >> 16);
    digest[i * 4 + 2] = (uint8_t)(H[i] >>  8);
    digest[i * 4 + 3] = (uint8_t)(H[i]      );
  }
}

void sha256_to_hex(const uint8_t digest[SHA256_DIGEST_BYTES],
                   char hex_out[SHA256_HEX_BYTES]) {
  static const char *hex = "0123456789abcdef";
  for (int i = 0; i < SHA256_DIGEST_BYTES; i++) {
    hex_out[i * 2 + 0] = hex[(digest[i] >> 4) & 0xF];
    hex_out[i * 2 + 1] = hex[ digest[i]       & 0xF];
  }
  hex_out[SHA256_DIGEST_BYTES * 2] = '\0';
}
