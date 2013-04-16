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

struct process *process_create(pid_t pid, struct thread *t);
pid_t process_give_pid();

#endif /* _PROCESS_H_ */
