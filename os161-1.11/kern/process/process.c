#include <process.h>
#include <thread.h>

static struct process *
process_create(struct process *p, pid_t pid, struct thread *t) {
  p->pid = pid;
  pid->t = t;
  p->did_exit = 0;
  p->exit_code = 0;
}
