#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);
int _helloworld();
int _printint(int value);
int _printstring(char *string, int numchars);
int printchar(char c);
int getpid();
int execv(const char *prog, char **args);
char readchar();
void _exit(int code);


#endif /* _SYSCALL_H_ */
