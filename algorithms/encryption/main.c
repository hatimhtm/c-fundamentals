/**
 * @file main.c
 * @brief CLI for Caesar + Vigenère ciphers with chi-squared cracker.
 *
 * Usage:
 *   crypto -e SHIFT "text"          # Caesar encrypt
 *   crypto -d SHIFT "text"          # Caesar decrypt
 *   crypto -c "ciphertext"          # Caesar crack via chi-squared
 *   crypto -v --key=KEY "text"      # Vigenère encrypt
 *   crypto -V --key=KEY "ciphertext" # Vigenère decrypt
 *
 * Avoids the previous fixed-1024-byte buffer by allocating exactly the
 * needed size from concatenated argv tail.
 */

#include "caesar.h"
#include "vigenere.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_usage(const char *prog) {
  printf("Usage:\n");
  printf("  %s -e SHIFT \"text\"          # Caesar encrypt\n", prog);
  printf("  %s -d SHIFT \"text\"          # Caesar decrypt\n", prog);
  printf("  %s -c \"ciphertext\"          # Caesar crack (chi-squared)\n", prog);
  printf("  %s -v --key=KEY \"text\"      # Vigenère encrypt\n", prog);
  printf("  %s -V --key=KEY \"text\"      # Vigenère decrypt\n", prog);
  printf("\nExamples:\n");
  printf("  %s -e 3 \"Hello World\"               # → Khoor Zruog\n", prog);
  printf("  %s -c \"Khoor Zruog\"                 # → guesses shift 3\n", prog);
  printf("  %s -v --key=lemon \"attack at dawn\"  # → lxfopv ef rnhr\n", prog);
}

/** Joins argv[start..argc-1] with single spaces into a fresh malloc'd buffer. */
static char *join_args(int argc, char *argv[], int start) {
  if (start >= argc) return NULL;
  size_t total = 0;
  for (int i = start; i < argc; i++) total += strlen(argv[i]) + 1; /* +space */
  char *buf = malloc(total + 1);
  if (!buf) return NULL;
  buf[0] = '\0';
  for (int i = start; i < argc; i++) {
    if (i > start) strcat(buf, " ");
    strcat(buf, argv[i]);
  }
  return buf;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  enum { NONE, CAESAR_ENC, CAESAR_DEC, CAESAR_CRACK, VIGENERE_ENC, VIGENERE_DEC } mode = NONE;
  int shift = 0;
  const char *key = NULL;

  static struct option long_opts[] = {
    {"encrypt",    required_argument, 0, 'e'},
    {"decrypt",    required_argument, 0, 'd'},
    {"crack",      no_argument,       0, 'c'},
    {"vigenere",   no_argument,       0, 'v'},
    {"vdecrypt",   no_argument,       0, 'V'},
    {"key",        required_argument, 0, 'k'},
    {"help",       no_argument,       0, 'h'},
    {0, 0, 0, 0}
  };

  int opt;
  while ((opt = getopt_long(argc, argv, "e:d:cvVk:h", long_opts, NULL)) != -1) {
    switch (opt) {
      case 'e': mode = CAESAR_ENC;    shift = atoi(optarg); break;
      case 'd': mode = CAESAR_DEC;    shift = atoi(optarg); break;
      case 'c': mode = CAESAR_CRACK;  break;
      case 'v': mode = VIGENERE_ENC;  break;
      case 'V': mode = VIGENERE_DEC;  break;
      case 'k': key = optarg;         break;
      case 'h': print_usage(argv[0]); return EXIT_SUCCESS;
      default:  print_usage(argv[0]); return EXIT_FAILURE;
    }
  }

  if (mode == NONE) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  char *text = join_args(argc, argv, optind);
  if (!text) {
    fprintf(stderr, "Error: no text supplied or out of memory\n");
    return EXIT_FAILURE;
  }

  int rc = EXIT_SUCCESS;
  switch (mode) {
    case CAESAR_ENC:
      caesar_encrypt(text, shift);
      printf("%s\n", text);
      break;
    case CAESAR_DEC:
      caesar_decrypt(text, shift);
      printf("%s\n", text);
      break;
    case CAESAR_CRACK: {
      int guessed = caesar_crack(text);
      printf("Guessed shift: %d\n", guessed);
      char *copy = strdup(text);
      if (copy) {
        caesar_decrypt(copy, guessed);
        printf("Decrypted: %s\n", copy);
        free(copy);
      }
      break;
    }
    case VIGENERE_ENC:
    case VIGENERE_DEC:
      if (!key) {
        fprintf(stderr, "Error: --key=KEY is required for Vigenère.\n");
        rc = EXIT_FAILURE;
        break;
      }
      if (mode == VIGENERE_ENC) vigenere_encrypt(text, key);
      else                      vigenere_decrypt(text, key);
      printf("%s\n", text);
      break;
    case NONE:
      break;
  }

  free(text);
  return rc;
}
