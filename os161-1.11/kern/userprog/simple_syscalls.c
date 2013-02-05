#include <types.h>
#include <syscall.h>

int _helloworld() {
  return kprintf("Hello World\n");
}

int _printint(int value) {
  return kprintf("%d", value);
}

int _printstring(char *string, int numchars) {
  //return 
}

void _exit(int code) {
  return thread_exit();
}
