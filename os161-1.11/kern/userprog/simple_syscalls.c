#include <types.h>
#include <syscall.h>
#include <curthread.h>
#include <thread.h>

int errno = 0; // Required
#include <errno.h>
#include <lib.h>
#include <stdio.h>
#include <lib.h>
#include <machine/spl.h>
#include <process.h>
#include <machine/trapframe.h>

int _helloworld() {
  return kprintf("Hello World\n");
}

int _printint(int value) {
  return kprintf("%d", value);
}

int _printstring(char *string, int numchars) {
  char str[255];
  size_t actual;
  copyinstr((void*)string, str, numchars+1, &actual);
  if  (str[numchars] == '\0' && (int)strlen(str) == numchars) {
    return kprintf(str);
  }
  errno = -1; // Todo: correct this errno
  return errno;
}

pid_t getpid() {
  //return curthread->process->pid;
}

/* char readchar(void)
 * Reads and returns a char from standard input.
 */
char readchar(void) {
  int result;
  result = getch();
  if(result == 0) {
    /*
     * A return value of 0 should be construed as signifying end-of-file.
     */
  } else if (result == -1) {
    if (errno == EBADF) {
      // `fd` is not a valid file descriptor, or was not opened for reading.
    } else if (errno == EFAULT) {
      // Part or all of the address space pointed to by `buf` is invalid.
    } else if (errno == EIO) {
      // A hardware I/O error occurred reading the data.
    }
  }
  return result;
}

/* void printchar(char)
 * Prints its argument to standard output.
 */
int printchar(char c) {
  int result;
  putch(c);
  // Todo: result isn't used
  if (result == 0) {
    /*
     * A return value of 0 means that nothing could be written, but that no
     * error occurred; this only occurs at end-of-file on fixed-size objects.
     */
    return 0;
  } else if (result == -1) {
    if (errno == EBADF) {
      // `fd` is not a valid file descriptor, or was not opened for writing.
    } else if (errno == EFAULT) {
      // Part or all of the addres space pointed to by `buf` is invalid.
    } else if (errno == ENOSPC) {
      // There is no free space remaining on the filesystem containing the file.
    } else if (errno == EIO) {
      // A hardware I/O error occurred writing the data.
    }
    return -1;
  }
  return 0;
}

struct process_extras {
  struct trapframe *tf;
  struct addrspace *ar;
  pid_t pid; // child pid
};

void md_entry(void *data1, unsigned long data2) {
  struct process_extras *pe = (struct process_extras *) data1;  
  curthread->t_vmspace = pe->ar;
  struct trapframe new_tf;
  memcpy(&new_tf, pe->tf, sizeof(struct trapframe));
  new_tf.tf_epc += 4;
  new_tf.tf_v0 = 0;

  process_create(pe->pid, curthread);

  mips_usermode(&new_tf);
}

pid_t fork(struct trapframe *tf, int *retvalue) {
  int err;

  struct trapframe *new_tf = NULL;
  memcpy(new_tf, tf, sizeof(struct trapframe)); //memcpy trapframe
  struct addrspace *new_ar = NULL;
  as_copy(curthread->t_vmspace, &new_ar); // new address space

  //as_activate(curthread->t_vmspace);

  pid_t pid = process_give_pid();
  struct process_extras p_extras = {new_tf, new_ar, pid};

  err = thread_fork("child", &p_extras, 0, md_entry, NULL); // pass in function
  *retvalue = pid;
  return err;
}

void execv() {
  // Todo -- the heart of the assignment
}

void waitpid() {
  // Todo
}

void _exit(int code) {
  code = code;
  return thread_exit();
}
