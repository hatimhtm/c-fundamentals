/**
 * @file signal_demo.c
 * @brief POSIX signal-handling demo — graceful shutdown on SIGINT/SIGTERM.
 *
 * Installs a `sigaction` handler for SIGINT (Ctrl-C) and SIGTERM that
 * sets a `volatile sig_atomic_t` flag. The main loop polls the flag
 * once per second and exits cleanly when it's set, demonstrating the
 * signal-safe pattern for graceful shutdown.
 *
 * Why `sig_atomic_t volatile` and not a plain int? Because the handler
 * runs asynchronously with respect to main; without `volatile` the
 * compiler may cache the read in a register, and without `sig_atomic_t`
 * the read or write may not be atomic on some platforms.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static volatile sig_atomic_t g_should_exit = 0;
static volatile sig_atomic_t g_last_signal = 0;

static void on_signal(int signo) {
  g_last_signal = signo;
  g_should_exit = 1;
}

static const char *signal_name(int signo) {
  switch (signo) {
    case SIGINT:  return "SIGINT";
    case SIGTERM: return "SIGTERM";
    case SIGHUP:  return "SIGHUP";
    default:      return "?";
  }
}

int main(int argc, char *argv[]) {
  int max_seconds = 30;
  if (argc > 1) max_seconds = atoi(argv[1]);
  if (max_seconds <= 0) max_seconds = 30;

  /* Install handlers via sigaction (signal() has portability quirks). */
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = on_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0; /* no SA_RESTART — we want sleep() to be interrupted */

  if (sigaction(SIGINT,  &sa, NULL) < 0) { perror("sigaction SIGINT");  return 1; }
  if (sigaction(SIGTERM, &sa, NULL) < 0) { perror("sigaction SIGTERM"); return 1; }
  if (sigaction(SIGHUP,  &sa, NULL) < 0) { perror("sigaction SIGHUP");  return 1; }

  printf("signal-demo: PID %d, max %d seconds\n", getpid(), max_seconds);
  printf("Press Ctrl-C (SIGINT) or send SIGTERM to exit gracefully.\n\n");

  for (int i = 0; i < max_seconds && !g_should_exit; i++) {
    printf("  tick %2d\n", i + 1);
    fflush(stdout);
    sleep(1);
  }

  if (g_should_exit) {
    printf("\nReceived %s — shutting down cleanly.\n", signal_name(g_last_signal));
  } else {
    printf("\nReached %d-second cap — exiting normally.\n", max_seconds);
  }
  return 0;
}
