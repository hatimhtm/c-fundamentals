/**
 * @file sysinfo.c
 * @brief Cross-platform system information utility
 *
 * Displays system information using POSIX uname() and other
 * system calls. Works on Unix-like systems (Linux, macOS, BSD).
 */

#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

#ifdef __APPLE__
#include <sys/sysctl.h>
#endif

void print_separator(void) {
  printf("----------------------------------------\n");
}

void print_uname_info(void) {
  struct utsname buffer;

  if (uname(&buffer) < 0) {
    perror("uname");
    return;
  }

  printf("System Information\n");
  print_separator();
  printf("  %-15s %s\n", "OS:", buffer.sysname);
  printf("  %-15s %s\n", "Hostname:", buffer.nodename);
  printf("  %-15s %s\n", "Release:", buffer.release);
  printf("  %-15s %s\n", "Version:", buffer.version);
  printf("  %-15s %s\n", "Architecture:", buffer.machine);

#ifdef _GNU_SOURCE
  printf("  %-15s %s\n", "Domain:", buffer.domainname);
#endif
}

void print_user_info(void) {
  printf("\nUser Information\n");
  print_separator();

  uid_t uid = getuid();
  uid_t euid = geteuid();
  gid_t gid = getgid();

  struct passwd *pw = getpwuid(uid);

  if (pw != NULL) {
    printf("  %-15s %s\n", "Username:", pw->pw_name);
    printf("  %-15s %s\n", "Home:", pw->pw_dir);
    printf("  %-15s %s\n", "Shell:", pw->pw_shell);
  }

  printf("  %-15s %d\n", "UID:", uid);
  printf("  %-15s %d\n", "Effective UID:", euid);
  printf("  %-15s %d\n", "GID:", gid);
}

void print_cpu_info(void) {
  printf("\nCPU Information\n");
  print_separator();

#ifdef __APPLE__
  char cpu_brand[256];
  size_t size = sizeof(cpu_brand);

  if (sysctlbyname("machdep.cpu.brand_string", &cpu_brand, &size, NULL, 0) ==
      0) {
    printf("  %-15s %s\n", "CPU:", cpu_brand);
  }

  int ncpu;
  size = sizeof(ncpu);
  if (sysctlbyname("hw.ncpu", &ncpu, &size, NULL, 0) == 0) {
    printf("  %-15s %d\n", "CPU Cores:", ncpu);
  }
#else
  long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  if (nprocs > 0) {
    printf("  %-15s %ld\n", "CPU Cores:", nprocs);
  }
#endif
}

void print_memory_info(void) {
  printf("\nMemory Information\n");
  print_separator();

#ifdef __APPLE__
  int64_t memsize;
  size_t size = sizeof(memsize);

  if (sysctlbyname("hw.memsize", &memsize, &size, NULL, 0) == 0) {
    printf("  %-15s %.2f GB\n", "Total RAM:", memsize / (1024.0 * 1024 * 1024));
  }
#else
  long pages = sysconf(_SC_PHYS_PAGES);
  long page_size = sysconf(_SC_PAGE_SIZE);

  if (pages > 0 && page_size > 0) {
    double gb = (double)pages * page_size / (1024.0 * 1024 * 1024);
    printf("  %-15s %.2f GB\n", "Total RAM:", gb);
  }
#endif
}

int main(int argc, char *argv[]) {
  int verbose = 0;

  // Simple argument parsing
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
      verbose = 1;
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("Usage: %s [-v|--verbose] [-h|--help]\n", argv[0]);
      printf("\nDisplay system information.\n");
      printf("\nOptions:\n");
      printf("  -v, --verbose  Show detailed information\n");
      printf("  -h, --help     Show this help message\n");
      return EXIT_SUCCESS;
    }
  }

  printf("\n");
  print_uname_info();

  if (verbose) {
    print_user_info();
    print_cpu_info();
    print_memory_info();
  }

  printf("\n");
  return EXIT_SUCCESS;
}
