# C Fundamentals — unified Makefile
# Targets:
#   make all            build every binary into build/
#   make sorting        build/sorting
#   make searching      build/bsearch
#   make crypto         build/crypto-cli
#   make sysinfo        build/sysinfo
#   make signals        build/signal-demo
#   make linked-list    build/linked-list-demo
#   make hash-table     build/hash-table-demo
#   make benchmark      build/benchmark
#   make test           run the unit-test suite
#   make smoke          smoke-test every CLI binary
#   make asan           rebuild + run tests with AddressSanitizer
#   make ubsan          rebuild + run tests with UndefinedBehaviorSanitizer
#   make clean          rm -rf build/

CC      ?= cc
# Feature-test macros:
#   _POSIX_C_SOURCE=200809L  → strdup, clock_gettime, getopt_long, statvfs etc.
#   _DARWIN_C_SOURCE         → re-enable BSD types Apple's headers gate behind it
CFLAGS  ?= -Wall -Wextra -Werror -std=c11 -O2 -pedantic \
           -D_POSIX_C_SOURCE=200809L -D_DARWIN_C_SOURCE
LDFLAGS ?=

BUILD_DIR := build

.PHONY: all clean test smoke asan ubsan install \
        sorting searching crypto sysinfo signals \
        linked-list hash-table benchmark

all: sorting searching crypto sysinfo signals linked-list hash-table benchmark

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# ─── Sorting library + CLI ────────────────────────────────────────────
SORT_DIR := algorithms/sorting
SORT_LIB_SRC := $(SORT_DIR)/selection_sort.c \
                $(SORT_DIR)/insertion_sort.c \
                $(SORT_DIR)/bubble_sort.c    \
                $(SORT_DIR)/quicksort.c      \
                $(SORT_DIR)/merge_sort.c     \
                $(SORT_DIR)/heap_sort.c      \
                $(SORT_DIR)/radix_sort.c
SORT_LIB_OBJ := $(SORT_LIB_SRC:%.c=$(BUILD_DIR)/%.o)

# Heap sort delegates max-heap sift-down to the heap module.
HEAP_DIR    := data_structures/heap
HEAP_LIB    := $(BUILD_DIR)/$(HEAP_DIR)/heap.o

sorting: $(BUILD_DIR)/sorting
	@echo "✓ built $(BUILD_DIR)/sorting"

$(BUILD_DIR)/sorting: $(SORT_LIB_OBJ) $(BUILD_DIR)/$(SORT_DIR)/main.o $(HEAP_LIB) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(SORT_DIR)/%.o: $(SORT_DIR)/%.c $(SORT_DIR)/sorts.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Searching ────────────────────────────────────────────────────────
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

# ─── Crypto ───────────────────────────────────────────────────────────
CRYPTO_DIR := algorithms/encryption
CRYPTO_LIB := $(BUILD_DIR)/$(CRYPTO_DIR)/caesar.o \
              $(BUILD_DIR)/$(CRYPTO_DIR)/vigenere.o \
              $(BUILD_DIR)/$(CRYPTO_DIR)/xor_cipher.o \
              $(BUILD_DIR)/$(CRYPTO_DIR)/sha256.o

crypto: $(BUILD_DIR)/crypto-cli
	@echo "✓ built $(BUILD_DIR)/crypto-cli"

$(BUILD_DIR)/crypto-cli: $(CRYPTO_LIB) $(BUILD_DIR)/$(CRYPTO_DIR)/main.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(CRYPTO_DIR)/%.o: $(CRYPTO_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Sysinfo ──────────────────────────────────────────────────────────
SYSINFO_DIR := systems/sysinfo

sysinfo: $(BUILD_DIR)/sysinfo
	@echo "✓ built $(BUILD_DIR)/sysinfo"

$(BUILD_DIR)/sysinfo: $(SYSINFO_DIR)/sysinfo.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# ─── Signal demo ──────────────────────────────────────────────────────
SIGNALS_DIR := systems/signals

signals: $(BUILD_DIR)/signal-demo
	@echo "✓ built $(BUILD_DIR)/signal-demo"

$(BUILD_DIR)/signal-demo: $(SIGNALS_DIR)/signal_demo.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# ─── Linked list demo + library ───────────────────────────────────────
LL_DIR := data_structures/linked_list

linked-list: $(BUILD_DIR)/linked-list-demo
	@echo "✓ built $(BUILD_DIR)/linked-list-demo"

$(BUILD_DIR)/linked-list-demo: $(BUILD_DIR)/$(LL_DIR)/linked_list.o \
                               $(BUILD_DIR)/$(LL_DIR)/main.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(LL_DIR)/%.o: $(LL_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Hash table demo + library ────────────────────────────────────────
HT_DIR := data_structures/hash_table

hash-table: $(BUILD_DIR)/hash-table-demo
	@echo "✓ built $(BUILD_DIR)/hash-table-demo"

$(BUILD_DIR)/hash-table-demo: $(BUILD_DIR)/$(HT_DIR)/hash_table.o \
                              $(BUILD_DIR)/$(HT_DIR)/main.o | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(HT_DIR)/%.o: $(HT_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Stack / Queue / BST / Heap / Trie libraries (no standalone CLI) ──
STACK_DIR  := data_structures/stack
QUEUE_DIR  := data_structures/queue
BST_DIR    := data_structures/bst
TRIE_DIR   := data_structures/trie

DS_LIB_OBJS := $(BUILD_DIR)/$(STACK_DIR)/stack.o \
               $(BUILD_DIR)/$(QUEUE_DIR)/queue.o \
               $(BUILD_DIR)/$(BST_DIR)/bst.o     \
               $(HEAP_LIB)                       \
               $(BUILD_DIR)/$(TRIE_DIR)/trie.o

$(BUILD_DIR)/$(STACK_DIR)/%.o: $(STACK_DIR)/%.c $(STACK_DIR)/stack.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(QUEUE_DIR)/%.o: $(QUEUE_DIR)/%.c $(QUEUE_DIR)/queue.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(BST_DIR)/%.o: $(BST_DIR)/%.c $(BST_DIR)/bst.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(HEAP_DIR)/%.o: $(HEAP_DIR)/%.c $(HEAP_DIR)/heap.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(TRIE_DIR)/%.o: $(TRIE_DIR)/%.c $(TRIE_DIR)/trie.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# ─── Benchmark ────────────────────────────────────────────────────────
benchmark: $(BUILD_DIR)/benchmark
	@echo "✓ built $(BUILD_DIR)/benchmark"

$(BUILD_DIR)/benchmark: $(SORT_LIB_OBJ) $(BUILD_DIR)/$(SORT_DIR)/benchmark.o $(HEAP_LIB) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# ─── Tests ────────────────────────────────────────────────────────────
TESTS_DIR := tests
TESTS_SRC := $(TESTS_DIR)/test_runner.c     \
             $(TESTS_DIR)/test_sorts.c      \
             $(TESTS_DIR)/test_search.c     \
             $(TESTS_DIR)/test_caesar.c     \
             $(TESTS_DIR)/test_vigenere.c   \
             $(TESTS_DIR)/test_xor.c        \
             $(TESTS_DIR)/test_sha256.c     \
             $(TESTS_DIR)/test_linked_list.c \
             $(TESTS_DIR)/test_stack.c      \
             $(TESTS_DIR)/test_queue.c      \
             $(TESTS_DIR)/test_bst.c        \
             $(TESTS_DIR)/test_heap.c       \
             $(TESTS_DIR)/test_trie.c       \
             $(TESTS_DIR)/test_hash_table.c
TESTS_OBJ := $(TESTS_SRC:%.c=$(BUILD_DIR)/%.o)

TESTS_LINK_OBJS := $(SORT_LIB_OBJ)                         \
                   $(BUILD_DIR)/$(SEARCH_DIR)/binary_search.o \
                   $(CRYPTO_LIB)                            \
                   $(BUILD_DIR)/$(LL_DIR)/linked_list.o     \
                   $(BUILD_DIR)/$(HT_DIR)/hash_table.o      \
                   $(DS_LIB_OBJS)

$(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c $(TESTS_DIR)/test.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/test-runner: $(TESTS_OBJ) $(TESTS_LINK_OBJS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

test: $(BUILD_DIR)/test-runner
	@echo "\n── Unit tests ──"
	@$(BUILD_DIR)/test-runner

# ─── Sanitizer builds ─────────────────────────────────────────────────
asan:
	@echo "── AddressSanitizer pass ──"
	$(MAKE) clean
	$(MAKE) test CFLAGS='-Wall -Wextra -Werror -std=c11 -O1 -g -pedantic \
                          -D_POSIX_C_SOURCE=200809L -D_DARWIN_C_SOURCE \
                          -fsanitize=address -fno-omit-frame-pointer' \
              LDFLAGS='-fsanitize=address'

ubsan:
	@echo "── UndefinedBehaviorSanitizer pass ──"
	$(MAKE) clean
	$(MAKE) test CFLAGS='-Wall -Wextra -Werror -std=c11 -O1 -g -pedantic \
                          -D_POSIX_C_SOURCE=200809L -D_DARWIN_C_SOURCE \
                          -fsanitize=undefined -fno-omit-frame-pointer' \
              LDFLAGS='-fsanitize=undefined'

# ─── Smoke tests ──────────────────────────────────────────────────────
smoke: all
	@echo "\n── Smoke ──"
	@$(BUILD_DIR)/sorting --algo=quick zebra ant mouse cat > /dev/null && echo "✓ sorting --algo=quick"
	@$(BUILD_DIR)/sorting --algo=heap   apple zebra mango   > /dev/null && echo "✓ sorting --algo=heap"
	@$(BUILD_DIR)/bsearch 7 3 1 9 7 4 2 > /dev/null && echo "✓ bsearch"
	@$(BUILD_DIR)/crypto-cli -e 3 "Hello" > /dev/null && echo "✓ crypto-cli caesar"
	@$(BUILD_DIR)/crypto-cli -v --key=lemon "attack at dawn" > /dev/null && echo "✓ crypto-cli vigenere"
	@$(BUILD_DIR)/crypto-cli -x --key=secret "hi"  > /dev/null && echo "✓ crypto-cli xor"
	@$(BUILD_DIR)/crypto-cli -s "abc"              > /dev/null && echo "✓ crypto-cli sha256"
	@$(BUILD_DIR)/sysinfo > /dev/null && echo "✓ sysinfo"
	@$(BUILD_DIR)/signal-demo 1 > /dev/null && echo "✓ signal-demo"
	@$(BUILD_DIR)/linked-list-demo 1 2 3 > /dev/null && echo "✓ linked-list"
	@$(BUILD_DIR)/hash-table-demo the cat sat the > /dev/null && echo "✓ hash-table"
	@$(BUILD_DIR)/benchmark > /dev/null && echo "✓ benchmark"
	@echo "\n✓ All smoke tests passed."

# ─── Clean ────────────────────────────────────────────────────────────
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ cleaned $(BUILD_DIR)"

# ─── Install ──────────────────────────────────────────────────────────
PREFIX ?= /usr/local

install: all
	install -d $(PREFIX)/bin
	install -m 755 $(BUILD_DIR)/sorting           $(PREFIX)/bin/cf-sort
	install -m 755 $(BUILD_DIR)/bsearch           $(PREFIX)/bin/cf-bsearch
	install -m 755 $(BUILD_DIR)/crypto-cli        $(PREFIX)/bin/cf-crypto
	install -m 755 $(BUILD_DIR)/sysinfo           $(PREFIX)/bin/cf-sysinfo
	install -m 755 $(BUILD_DIR)/signal-demo       $(PREFIX)/bin/cf-signals
	install -m 755 $(BUILD_DIR)/linked-list-demo  $(PREFIX)/bin/cf-linked-list
	install -m 755 $(BUILD_DIR)/hash-table-demo   $(PREFIX)/bin/cf-hash-table
	install -m 755 $(BUILD_DIR)/benchmark         $(PREFIX)/bin/cf-bench
	@echo "✓ installed to $(PREFIX)/bin"
