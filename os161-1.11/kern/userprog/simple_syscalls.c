#include <types.h>
#include <syscall.h>

int _helloworld() {
  return kprintf("Hello World\n");
}

int _printint(int value) {
  return kprintf("%d", value);
}

int _printstring(char *string, int numchars) {
  char str[255];
  strcpy(str, string); 
  if  (str[numchars] == '\0' && strlen(str) == numchars) {
    return kprintf(str);
  }
  int errno = -1; // Todo: correct this errno
  return errno;
}

void _exit(int code) {
  return thread_exit();
}
