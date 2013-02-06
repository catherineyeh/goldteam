#include <types.h>
#include <syscall.h>

int _helloworld() {
  return kprintf("Hello World\n");
}

int _printint(int value) {
  return kprintf("%d", value);
}

int _printstring(char *string, int numchars) {
  /*
   * Copy the string from the user address into a kernel buffer, and then print
   * it using kprintf. Be careful to check for misuse by the user (for example,
   * the memory pointed to by "string" may not contain a proper null-terminated
   * string of length numchars). If an error is detected, errno should be set
   * and an appropriate result returned. Otherwise, the return value should be
   * the return value from kprintf.
   */
  char *str = string;
  if (strlen(str) == numchars)
    return kprintf(string);
  /*
  errno = 1; // Todo: correct this errno
  return errno;
  */
}

void _exit(int code) {
  return thread_exit();
}
