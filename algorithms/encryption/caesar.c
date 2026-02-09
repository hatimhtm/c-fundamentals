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
  if (text == NULL || strlen(text) == 0) {
    return 0;
  }

  // Count frequency of each letter
  int freq[26] = {0};
  int total = 0;

  for (size_t i = 0; text[i] != '\0'; i++) {
    if (isalpha(text[i])) {
      freq[toupper(text[i]) - 'A']++;
      total++;
    }
  }

  if (total == 0)
    return 0;

  // In English, 'E' is the most common letter
  // Find the most frequent letter in ciphertext
  int max_freq = 0;
  int max_idx = 0;

  for (int i = 0; i < 26; i++) {
    if (freq[i] > max_freq) {
      max_freq = freq[i];
      max_idx = i;
    }
  }

  // Calculate shift assuming most frequent = 'E' (index 4)
  int shift = (max_idx - 4 + 26) % 26;

  return shift;
}
