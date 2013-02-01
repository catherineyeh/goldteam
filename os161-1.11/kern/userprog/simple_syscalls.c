#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <uio.h>
#include <addrspace.h>
#include <thread.h>
#include <curthread.h>
#include <vnode.h>

int _helloworld() {
  return kprintf("Hello World\n");
}

int _printint(int value) {
  return kprintf(value);
}
