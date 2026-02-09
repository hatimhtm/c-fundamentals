# C Fundamentals

[![Build](https://github.com/hatimhtm/c-fundamentals/actions/workflows/build.yml/badge.svg)](https://github.com/hatimhtm/c-fundamentals/actions/workflows/build.yml)
[![C](https://img.shields.io/badge/C-11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

> A collection of fundamental computer science implementations in C.

This repository demonstrates core CS concepts including algorithms, data structures, and systems programming with clean, well-documented code.

## 📁 Structure

```
c-fundamentals/
├── algorithms/
│   ├── sorting/          # Selection sort implementation
│   └── encryption/       # Caesar cipher with frequency analysis
├── systems/
│   └── sysinfo/          # Cross-platform system information
├── Makefile              # Unified build system
└── README.md
```

## 🛠️ Building

```bash
# Build all modules
make all

# Build specific module
make sorting
make encryption
make sysinfo

# Run tests
make test

# Clean build files
make clean
```

## 📦 Modules

### Selection Sort (`algorithms/sorting/`)

Classic selection sort algorithm for sorting strings and integers.

```bash
# Interactive mode
./build/sorting

# With command-line arguments
./build/sorting banana apple cherry
# Output: ["apple", "banana", "cherry"]
```

**Complexity:** O(n²) time, O(1) space

---

### Caesar Cipher (`algorithms/encryption/`)

The classic Caesar cipher with encryption, decryption, and frequency analysis cracking.

```bash
# Encrypt with shift 3
./build/caesar-cli -e 3 "Hello World"
# Output: Khoor Zruog

# Decrypt
./build/caesar-cli -d 3 "Khoor Zruog"
# Output: Hello World

# Crack (frequency analysis)
./build/caesar-cli -c "Khoor Zruog"
# Output: Guessed shift: 3
#         Decrypted: Hello World
```

---

### System Info (`systems/sysinfo/`)

Cross-platform utility to display system information.

```bash
# Basic info
./build/sysinfo

# Verbose (includes CPU, memory, user info)
./build/sysinfo -v
```

**Supported platforms:** Linux, macOS, BSD

## 🔧 Technical Details

- **Standard:** C11
- **Compiler:** GCC/Clang with `-Wall -Wextra -Werror`
- **Platform:** POSIX-compliant (Linux, macOS, BSD)
- **Build:** Make

## 📚 Learning Goals

This project demonstrates:

| Concept | Implementation |
|---------|---------------|
| Algorithms | Selection sort, Caesar cipher |
| Data Structures | Arrays, strings |
| Systems Programming | POSIX APIs, sysctl |
| Build Systems | Makefile with multiple targets |
| Code Organization | Header files, modular design |
| Documentation | Doxygen-style comments |

## 🔨 Development

```bash
# Clone
git clone https://github.com/hatimhtm/c-fundamentals.git
cd c-fundamentals

# Build and test
make test

# Install (optional)
sudo make install PREFIX=/usr/local
```

## 📄 License

[MIT](LICENSE)
