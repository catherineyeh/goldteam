#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <thread.h>

struct process {
  pid_t pid;
  
  int did_exit;
  int exit_code;
  struct thread *t;
};

struct process *
process_create(struct process *p, int pid, struct thread* t) {
  p->pid = pid;
  p->t = t;
  p->did_exit = 0;
  p->exit_code = 0;
  return p;
}

#endif /* _PROCESS_H_ */
