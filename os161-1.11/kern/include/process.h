#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <thread.h>

struct process {
  pid_t pid;

  int did_exit;
  int exit_code;
  int newest_child_pid;

  struct thread *t;
};

struct process *process_create(struct process *p, pid_t pid, struct thread *t);

#endif /* _PROCESS_H_ */
