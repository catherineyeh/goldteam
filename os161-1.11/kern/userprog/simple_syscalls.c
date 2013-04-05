#include <types.h>
#include <syscall.h>

#include <kern/hash.h>

int _helloworld() {
  return kprintf("Hello World\n");
}

int _printint(int value) {
  return kprintf("%d", value);
}

int _printstring(char *string, int numchars) {
  char str[255];
  int actual;
  copyinstr(string, str, numchars+1, &actual);
  if  (str[numchars] == '\0' && strlen(str) == numchars) {
    return kprintf(str);
  }
  int errno = -1; // Todo: correct this errno
  return errno;
}

int getpid() {
  // Todo
}

char readchar(void) {
  // Todo
}

void fork() {
  // Todo
}

void execv() {
  // Todo -- the heart of the assignment
}

waitpid() {
  // Todo
}

void _exit(int code) {
  return thread_exit();
}
