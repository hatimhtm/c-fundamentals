# C Fundamentals
# Unified Makefile for building all modules

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -O2
LDFLAGS =

# Build directories
BUILD_DIR = build

# Targets
.PHONY: all clean sorting encryption sysinfo test

all: sorting encryption sysinfo

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ============================================================================
# Sorting module
# ============================================================================
SORTING_SRC = algorithms/sorting
SORTING_OBJS = $(BUILD_DIR)/selection_sort.o $(BUILD_DIR)/sorting_main.o

sorting: $(BUILD_DIR) $(BUILD_DIR)/sorting
	@echo "✓ Built: sorting"

$(BUILD_DIR)/sorting: $(SORTING_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/selection_sort.o: $(SORTING_SRC)/selection_sort.c $(SORTING_SRC)/selection_sort.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/sorting_main.o: $(SORTING_SRC)/main.c $(SORTING_SRC)/selection_sort.h
	$(CC) $(CFLAGS) -I$(SORTING_SRC) -c -o $@ $<

# ============================================================================
# Encryption module
# ============================================================================
ENCRYPT_SRC = algorithms/encryption
ENCRYPT_OBJS = $(BUILD_DIR)/caesar.o $(BUILD_DIR)/encrypt_main.o

encryption: $(BUILD_DIR) $(BUILD_DIR)/caesar-cli
	@echo "✓ Built: caesar-cli"

$(BUILD_DIR)/caesar-cli: $(ENCRYPT_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/caesar.o: $(ENCRYPT_SRC)/caesar.c $(ENCRYPT_SRC)/caesar.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/encrypt_main.o: $(ENCRYPT_SRC)/main.c $(ENCRYPT_SRC)/caesar.h
	$(CC) $(CFLAGS) -I$(ENCRYPT_SRC) -c -o $@ $<

# ============================================================================
# System Info module
# ============================================================================
SYSINFO_SRC = systems/sysinfo

sysinfo: $(BUILD_DIR) $(BUILD_DIR)/sysinfo
	@echo "✓ Built: sysinfo"

$(BUILD_DIR)/sysinfo: $(SYSINFO_SRC)/sysinfo.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# ============================================================================
# Test targets
# ============================================================================
test: all
	@echo "\n=== Testing Sorting ==="
	$(BUILD_DIR)/sorting banana apple cherry date
	@echo "\n=== Testing Caesar Cipher ==="
	$(BUILD_DIR)/caesar-cli -e 3 "Hello World"
	$(BUILD_DIR)/caesar-cli -d 3 "Khoor Zruog"
	@echo "\n=== Testing System Info ==="
	$(BUILD_DIR)/sysinfo
	@echo "\n✓ All tests passed!"

# ============================================================================
# Clean
# ============================================================================
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Cleaned build directory"

# ============================================================================
# Install (optional)
# ============================================================================
PREFIX ?= /usr/local

install: all
	install -d $(PREFIX)/bin
	install -m 755 $(BUILD_DIR)/sorting $(PREFIX)/bin/
	install -m 755 $(BUILD_DIR)/caesar-cli $(PREFIX)/bin/
	install -m 755 $(BUILD_DIR)/sysinfo $(PREFIX)/bin/
	@echo "✓ Installed to $(PREFIX)/bin"
