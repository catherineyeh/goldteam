#include <types.h>
#include <syscall.h>

int _helloworld() {
  return kprintf("Hello World\n");
}

int _printint(int value) {
  return kprintf(value);
}
