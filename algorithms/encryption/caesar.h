/**
 * @file caesar.h
 * @brief Caesar cipher encryption and decryption
 *
 * The Caesar cipher is one of the simplest encryption techniques.
 * It works by shifting each letter by a fixed number of positions
 * in the alphabet.
 */

#ifndef CAESAR_H
#define CAESAR_H

#include <stddef.h>

/**
 * @brief Encrypt a string using the Caesar cipher
 *
 * @param text The text to encrypt (modified in-place)
 * @param shift The number of positions to shift (0-25)
 *
 * @note Only alphabetic characters are encrypted; others remain unchanged
 * @note The shift is applied modulo 26
 */
void caesar_encrypt(char *text, int shift);

/**
 * @brief Decrypt a string encrypted with Caesar cipher
 *
 * @param text The text to decrypt (modified in-place)
 * @param shift The shift value used for encryption
 */
void caesar_decrypt(char *text, int shift);

/**
 * @brief Encrypt a single character
 *
 * @param c The character to encrypt
 * @param shift The shift value
 * @return The encrypted character
 */
char caesar_encrypt_char(char c, int shift);

/**
 * @brief Decrypt a single character
 *
 * @param c The character to decrypt
 * @param shift The shift value
 * @return The decrypted character
 */
char caesar_decrypt_char(char c, int shift);

/**
 * @brief Perform frequency analysis to guess the shift value
 *
 * @param text The encrypted text to analyze
 * @return The most likely shift value used
 */
int caesar_crack(const char *text);

#endif /* CAESAR_H */
