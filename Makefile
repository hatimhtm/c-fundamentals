# C Fundamentals — unified Makefile
# Targets:
#   make all            build every binary into build/
#   make sorting        build/sorting
#   make searching      build/bsearch
#   make crypto         build/crypto-cli
#   make sysinfo        build/sysinfo
#   make linked-list    build/linked-list-demo
#   make hash-table     build/hash-table-demo
#   make benchmark      build/benchmark
#   make test           run the unit-test suite
#   make smoke          smoke-test every CLI binary
#   make clean          rm -rf build/

CC      ?= cc
# Feature-test macros:
#   _POSIX_C_SOURCE=200809L  → strdup, clock_gettime, getopt_long under -std=c11
#                              (glibc otherwise hides POSIX functions in strict mode)
#   _DARWIN_C_SOURCE         → re-enable BSD-extension types (u_int, u_char,
#                              u_short, sysctlbyname) that Apple's headers gate
#                              behind this when _POSIX_C_SOURCE is set
CFLAGS  ?= -Wall -Wextra -Werror -std=c11 -O2 -pedantic \
           -D_POSIX_C_SOURCE=200809L -D_DARWIN_C_SOURCE
LDFLAGS ?=

BUILD_DIR := build

.PHONY: all clean test smoke install \
        sorting searching crypto sysinfo linked-list hash-table benchmark

all: sorting searching crypto sysinfo linked-list hash-table benchmark

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# ─── Sorting (build/sorting) ─────────────────────────────────────────
SORT_DIR := algorithms/sorting
SORT_LIB_SRC := $(SORT_DIR)/selection_sort.c \
                $(SORT_DIR)/insertion_sort.c \
                $(SORT_DIR)/bubble_sort.c    \
                $(SORT_DIR)/quicksort.c      \
                $(SORT_DIR)/merge_sort.c
SORT_LIB_OBJ := $(SORT_LIB_SRC:%.c=$(BUILD_DIR)/%.o)

sorting: $(BUILD_DIR)/sorting
	@echo "✓ built $(BUILD_DIR)/sorting"

$(BUILD_DIR)/sorting: $(SORT_LIB_OBJ) $(BUILD_DIR)/$(SORT_DIR)/main.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(SORT_DIR)/%.o: $(SORT_DIR)/%.c $(SORT_DIR)/sorts.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Searching (build/bsearch) ───────────────────────────────────────
SEARCH_DIR := algorithms/searching

searching: $(BUILD_DIR)/bsearch
	@echo "✓ built $(BUILD_DIR)/bsearch"

$(BUILD_DIR)/bsearch: $(BUILD_DIR)/$(SEARCH_DIR)/binary_search.o \
                     $(BUILD_DIR)/$(SEARCH_DIR)/main.o \
                     $(BUILD_DIR)/$(SORT_DIR)/insertion_sort.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(SEARCH_DIR)/%.o: $(SEARCH_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Crypto (build/crypto-cli) ───────────────────────────────────────
CRYPTO_DIR := algorithms/encryption
CRYPTO_LIB := $(BUILD_DIR)/$(CRYPTO_DIR)/caesar.o \
              $(BUILD_DIR)/$(CRYPTO_DIR)/vigenere.o

crypto: $(BUILD_DIR)/crypto-cli
	@echo "✓ built $(BUILD_DIR)/crypto-cli"

$(BUILD_DIR)/crypto-cli: $(CRYPTO_LIB) $(BUILD_DIR)/$(CRYPTO_DIR)/main.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(CRYPTO_DIR)/%.o: $(CRYPTO_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Sysinfo (build/sysinfo) ─────────────────────────────────────────
SYSINFO_DIR := systems/sysinfo

sysinfo: $(BUILD_DIR)/sysinfo
	@echo "✓ built $(BUILD_DIR)/sysinfo"

$(BUILD_DIR)/sysinfo: $(SYSINFO_DIR)/sysinfo.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# ─── Linked List demo (build/linked-list-demo) ──────────────────────
LL_DIR := data_structures/linked_list

linked-list: $(BUILD_DIR)/linked-list-demo
	@echo "✓ built $(BUILD_DIR)/linked-list-demo"

$(BUILD_DIR)/linked-list-demo: $(BUILD_DIR)/$(LL_DIR)/linked_list.o \
                               $(BUILD_DIR)/$(LL_DIR)/main.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(LL_DIR)/%.o: $(LL_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Hash Table demo (build/hash-table-demo) ────────────────────────
HT_DIR := data_structures/hash_table

hash-table: $(BUILD_DIR)/hash-table-demo
	@echo "✓ built $(BUILD_DIR)/hash-table-demo"

$(BUILD_DIR)/hash-table-demo: $(BUILD_DIR)/$(HT_DIR)/hash_table.o \
                              $(BUILD_DIR)/$(HT_DIR)/main.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(HT_DIR)/%.o: $(HT_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Benchmark (build/benchmark) ─────────────────────────────────────
benchmark: $(BUILD_DIR)/benchmark
	@echo "✓ built $(BUILD_DIR)/benchmark"

$(BUILD_DIR)/benchmark: $(SORT_LIB_OBJ) $(BUILD_DIR)/$(SORT_DIR)/benchmark.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# ─── Tests (build/tests) ─────────────────────────────────────────────
TESTS_DIR := tests
TESTS_SRC := $(TESTS_DIR)/test_runner.c \
             $(TESTS_DIR)/test_sorts.c  \
             $(TESTS_DIR)/test_search.c \
             $(TESTS_DIR)/test_caesar.c \
             $(TESTS_DIR)/test_vigenere.c \
             $(TESTS_DIR)/test_linked_list.c \
             $(TESTS_DIR)/test_hash_table.c
TESTS_OBJ := $(TESTS_SRC:%.c=$(BUILD_DIR)/%.o)

# Tests link against all module object files.
TESTS_LINK_OBJS := $(SORT_LIB_OBJ) \
                   $(BUILD_DIR)/$(SEARCH_DIR)/binary_search.o \
                   $(CRYPTO_LIB) \
                   $(BUILD_DIR)/$(LL_DIR)/linked_list.o \
                   $(BUILD_DIR)/$(HT_DIR)/hash_table.o

$(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c $(TESTS_DIR)/test.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/test-runner: $(TESTS_OBJ) $(TESTS_LINK_OBJS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

test: $(BUILD_DIR)/test-runner
	@echo "\n── Unit tests ──"
	@$(BUILD_DIR)/test-runner

# ─── Smoke test (run every binary at least once) ─────────────────────
smoke: all
	@echo "\n── Smoke: sorting ──"
	@$(BUILD_DIR)/sorting --algo=quick zebra ant mouse cat > /dev/null && echo "✓ sorting"
	@echo "── Smoke: bsearch ──"
	@$(BUILD_DIR)/bsearch 7 3 1 9 7 4 2 > /dev/null && echo "✓ bsearch"
	@echo "── Smoke: crypto-cli (caesar) ──"
	@$(BUILD_DIR)/crypto-cli -e 3 "Hello World" > /dev/null && echo "✓ crypto-cli encrypt"
	@$(BUILD_DIR)/crypto-cli -c "Khoor Zruog" > /dev/null && echo "✓ crypto-cli crack"
	@echo "── Smoke: crypto-cli (vigenere) ──"
	@$(BUILD_DIR)/crypto-cli -v --key=lemon "attack at dawn" > /dev/null && echo "✓ crypto-cli vigenere"
	@echo "── Smoke: sysinfo ──"
	@$(BUILD_DIR)/sysinfo > /dev/null && echo "✓ sysinfo"
	@echo "── Smoke: linked-list-demo ──"
	@$(BUILD_DIR)/linked-list-demo 1 2 3 > /dev/null && echo "✓ linked-list"
	@echo "── Smoke: hash-table-demo ──"
	@$(BUILD_DIR)/hash-table-demo the cat sat on the mat > /dev/null && echo "✓ hash-table"
	@echo "── Smoke: benchmark ──"
	@$(BUILD_DIR)/benchmark > /dev/null && echo "✓ benchmark"
	@echo "\n✓ All smoke tests passed."

# ─── Clean ───────────────────────────────────────────────────────────
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ cleaned $(BUILD_DIR)"

# ─── Install (CLI binaries only) ─────────────────────────────────────
PREFIX ?= /usr/local

install: all
	install -d $(PREFIX)/bin
	install -m 755 $(BUILD_DIR)/sorting           $(PREFIX)/bin/cf-sort
	install -m 755 $(BUILD_DIR)/bsearch           $(PREFIX)/bin/cf-bsearch
	install -m 755 $(BUILD_DIR)/crypto-cli        $(PREFIX)/bin/cf-crypto
	install -m 755 $(BUILD_DIR)/sysinfo           $(PREFIX)/bin/cf-sysinfo
	install -m 755 $(BUILD_DIR)/linked-list-demo  $(PREFIX)/bin/cf-linked-list
	install -m 755 $(BUILD_DIR)/hash-table-demo   $(PREFIX)/bin/cf-hash-table
	install -m 755 $(BUILD_DIR)/benchmark         $(PREFIX)/bin/cf-bench
	@echo "✓ installed to $(PREFIX)/bin"
