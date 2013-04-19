#include <unistd.h>
int main() {
  pid_t pid;
  pid = fork();
  pid = fork();
  getpid();
  _printstring("New process\n", 12);
  _exit(0);
  return 0;
}
