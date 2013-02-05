#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);
int _helloworld();
int _printint(int value);
int _printstring(char *string, int numchars);
void _exit(int code);


#endif /* _SYSCALL_H_ */
