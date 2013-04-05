
1. What are the ELF magic numbers?
2. What is the difference between `UIO_USERISPACE` and `UIO_USERSPACE`? When should one use `UIO_SYSSPACE` instead?
3. Why can the struct uio that is used to read in a segment be allocated on the stack in `load_segment()` (i.e., where does the memory read actually go)?
4. In `runprogram()`, why is it important to call `vfs_close()` before going to usermode?
5. What function forces the processor to switch into usermode? Is this function machine dependent?
6. In what file are `copyin` and `copyout` defined? Why can't `copyin` and `copyout` be implemented simply as `memmove`?
7. What is the purpose of `userptr_t`?
8. What is the numerical value of the exception code for a MIPS system call?
9. Why does mips_trap() set curspl to `SPL_HIGH` "manually", instead of using `splhigh()`?
10. How many bytes are in an instruction in MIPS? (Answer this by reading `mips_syscall()` carefully, not by looking somewhere else.)
11. Why do you "probably want to change" the implementation of `kill_curthread()`?
12. What would be required to implement a system call that took more than 4 arguments?
13. What is the purpose of the `SYSCALL` macro?
14. What is the MIPS instruction that actually triggers a system call? (Answer this by reading the source in this directory, not looking somewhere else.)