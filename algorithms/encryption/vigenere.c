/**
 * @file vigenere.c
 */

#include "vigenere.h"
#include <ctype.h>
#include <string.h>

static int key_shift(const char *key, size_t i) {
  size_t klen = strlen(key);
  if (klen == 0) return 0;
  char k = key[i % klen];
  if (!isalpha((unsigned char)k)) return 0;
  return (int)(tolower((unsigned char)k) - 'a');
}

static void vigenere_apply(char *text, const char *key, int direction) {
  if (!text || !key || strlen(key) == 0) return;

  size_t key_index = 0;
  for (size_t i = 0; text[i] != '\0'; i++) {
    if (!isalpha((unsigned char)text[i])) continue;

    int shift = key_shift(key, key_index) * direction;
    char base = isupper((unsigned char)text[i]) ? 'A' : 'a';
    int c = (text[i] - base + shift) % 26;
    if (c < 0) c += 26;
    text[i] = (char)(base + c);
    key_index++;
  }
}

void vigenere_encrypt(char *text, const char *key) { vigenere_apply(text, key, +1); }
void vigenere_decrypt(char *text, const char *key) { vigenere_apply(text, key, -1); }
