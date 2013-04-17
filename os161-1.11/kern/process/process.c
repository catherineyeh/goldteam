#include <types.h>
#include <lib.h>
#include <curthread.h>
#include <machine/spl.h>
#include <process.h>

struct process *processes[1000];
struct thread  *threads[1000];
pid_t last_pid_used = 1;

struct process *process_create(pid_t pid, struct thread *t) {
  struct process *p = kmalloc(sizeof(struct process));
  p->pid = pid;
  p->t = t;
  p->did_exit = 0;
  p->exit_code = 0;
  processes[pid] = p; // This is fine since process_give_pid returns the next
                      // available pid
  threads[pid] = t;
  return p;
}

pid_t process_getpid(struct thread *ct) {
  int i;
  for (i = 1; i < 1000; i = (i % 999) + 1) {
    if (threads[i] == ct) {
      return i;
    }
  }
}

pid_t process_give_pid() {
  int i;
  for (i = last_pid_used; i < 1000; i = (i % 999) + 1) {
    if (processes[i] == 0) {
      int s = splhigh();
      processes[i] = 1; // designating that it's being used because we don't
                        // want another process coming in and taking this pid
      threads[i] = 1;
      last_pid_used = i;
      splx(s);
      return last_pid_used;
    }
  }
}
