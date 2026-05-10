/**
 * @file caesar.c
 * @brief Implementation of Caesar cipher
 */

#include "caesar.h"
#include <ctype.h>
#include <string.h>

char caesar_encrypt_char(char c, int shift) {
  if (!isalpha(c)) {
    return c;
  }

  // Normalize shift to 0-25 range
  shift = ((shift % 26) + 26) % 26;

  char base = isupper(c) ? 'A' : 'a';
  return (char)(((c - base + shift) % 26) + base);
}

char caesar_decrypt_char(char c, int shift) {
  // Decryption is just encryption with negative shift
  return caesar_encrypt_char(c, -shift);
}

void caesar_encrypt(char *text, int shift) {
  if (text == NULL)
    return;

  for (size_t i = 0; text[i] != '\0'; i++) {
    text[i] = caesar_encrypt_char(text[i], shift);
  }
}

void caesar_decrypt(char *text, int shift) { caesar_encrypt(text, -shift); }

int caesar_crack(const char *text) {
  if (text == NULL || *text == '\0') return 0;

  /* Reference letter frequencies for English (percent). */
  static const double ENGLISH_FREQ[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
    0.77, 4.03, 2.41, 6.75,  7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
    2.76, 0.98, 2.36, 0.15,  1.97, 0.07
  };

  /* Tally cipher frequencies. */
  int counts[26] = {0};
  int total = 0;
  for (size_t i = 0; text[i] != '\0'; i++) {
    if (isalpha((unsigned char)text[i])) {
      counts[toupper((unsigned char)text[i]) - 'A']++;
      total++;
    }
  }
  if (total == 0) return 0;

  /* For each candidate shift, score plaintext by chi-squared distance from
     the English distribution. Lowest score wins. */
  double best_chi = 1e18;
  int best_shift = 0;
  for (int s = 0; s < 26; s++) {
    double chi = 0.0;
    for (int i = 0; i < 26; i++) {
      /* Decrypting with shift s rotates the cipher tally by -s. */
      double observed = (double)counts[(i + s) % 26];
      double expected = ENGLISH_FREQ[i] / 100.0 * (double)total;
      double delta = observed - expected;
      if (expected > 0) chi += (delta * delta) / expected;
    }
    if (chi < best_chi) {
      best_chi = chi;
      best_shift = s;
    }
  }

  return best_shift;
}
