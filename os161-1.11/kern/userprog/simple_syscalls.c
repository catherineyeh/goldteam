#include <types.h>
#include <syscall.h>
#include <curthread.h>
#include <thread.h>

#include <stdio.h>

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

int32_t getpid() {
  return curthread->pid;
}

/* char readchar(void)
 * Reads and returns a char from standard input.
 */
char readchar(void) {
  int c;
  //c = getchar();
  return c;
}

/* void printchar(char)
 * Prints its argument to standard output.
 */
void printchar(char c) {
  kprintf("%c", c);
}

void fork() {
  // Todo
}

void execv() {
  // Todo -- the heart of the assignment
}

void waitpid() {
  // Todo
}

void _exit(int code) {
  return thread_exit();
}
