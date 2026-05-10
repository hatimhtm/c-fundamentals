/**
 * @file vigenere.h
 * @brief Vigenère cipher — polyalphabetic shift keyed by a string.
 *
 * Conceptually a stack of 26 Caesar ciphers; the i-th letter of the
 * plaintext is shifted by the i-th letter of the key (key cycles).
 * Non-alphabetic characters pass through unchanged and do not advance
 * the key index.
 */

#ifndef VIGENERE_H
#define VIGENERE_H

void vigenere_encrypt(char *text, const char *key);
void vigenere_decrypt(char *text, const char *key);

#endif /* VIGENERE_H */
