/**
 * @file main.c
 * @brief Caesar cipher CLI tool
 */

#include "caesar.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *prog) {
  printf("Usage: %s [OPTIONS] <text>\n\n", prog);
  printf("Caesar cipher encryption and decryption tool.\n\n");
  printf("Options:\n");
  printf("  -e, --encrypt SHIFT  Encrypt text with given shift (0-25)\n");
  printf("  -d, --decrypt SHIFT  Decrypt text with given shift\n");
  printf("  -c, --crack          Attempt to crack the cipher\n");
  printf("  -h, --help           Show this help message\n\n");
  printf("Examples:\n");
  printf("  %s -e 3 \"Hello World\"    # Encrypt with shift 3\n", prog);
  printf("  %s -d 3 \"Khoor Zruog\"    # Decrypt with shift 3\n", prog);
  printf("  %s -c \"Khoor Zruog\"      # Crack the cipher\n", prog);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  int encrypt_mode = 0;
  int decrypt_mode = 0;
  int crack_mode = 0;
  int shift = 0;

  static struct option long_options[] = {{"encrypt", required_argument, 0, 'e'},
                                         {"decrypt", required_argument, 0, 'd'},
                                         {"crack", no_argument, 0, 'c'},
                                         {"help", no_argument, 0, 'h'},
                                         {0, 0, 0, 0}};

  int opt;
  while ((opt = getopt_long(argc, argv, "e:d:ch", long_options, NULL)) != -1) {
    switch (opt) {
    case 'e':
      encrypt_mode = 1;
      shift = atoi(optarg);
      break;
    case 'd':
      decrypt_mode = 1;
      shift = atoi(optarg);
      break;
    case 'c':
      crack_mode = 1;
      break;
    case 'h':
      print_usage(argv[0]);
      return EXIT_SUCCESS;
    default:
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
  }

  if (optind >= argc) {
    fprintf(stderr, "Error: No text provided\n");
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  // Concatenate remaining arguments as text
  char text[1024] = "";
  for (int i = optind; i < argc; i++) {
    if (i > optind)
      strcat(text, " ");
    strcat(text, argv[i]);
  }

  if (crack_mode) {
    int guessed_shift = caesar_crack(text);
    printf("Guessed shift: %d\n", guessed_shift);

    char decrypted[1024];
    strcpy(decrypted, text);
    caesar_decrypt(decrypted, guessed_shift);
    printf("Decrypted: %s\n", decrypted);
  } else if (encrypt_mode) {
    caesar_encrypt(text, shift);
    printf("%s\n", text);
  } else if (decrypt_mode) {
    caesar_decrypt(text, shift);
    printf("%s\n", text);
  } else {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
