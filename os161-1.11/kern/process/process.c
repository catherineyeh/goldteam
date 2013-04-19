#include <types.h>
#include <lib.h>
#include <curthread.h>
#include <machine/spl.h>
#include <process.h>

struct process *processes[1000];
pid_t last_pid_used = 1;

struct process *process_create(pid_t pid, struct thread *t) {
  struct process *p = kmalloc(sizeof(struct process));
  p->pid = pid;
  p->t = t;
  t->pid = pid;
  p->did_exit = 0;
  p->exit_code = 0;
  processes[pid] = p; // This is fine since process_give_pid returns the next
                      // available pid
  return p;
}

int process_remove_process(pid_t pid) {
  processes[pid] = 0;
}

pid_t process_give_pid() {
  int i;
  for (i = last_pid_used; i < 1000; i = (i % 999) + 1) {
    if (processes[i] == 0) {
      int s = splhigh();
      processes[i] = 1; // designating that it's being used because we don't
                        // want another process coming in and taking this pid
      last_pid_used = i;
      splx(s);
      return last_pid_used;
    }
  }
}

struct process *get_process(pid_t pid) {
  return processes[pid];
}
