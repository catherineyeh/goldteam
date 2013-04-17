#include <unistd.h>
int main() {
  pid_t pid;
  pid = fork();
  _printstring("New process\n", 12);
  return 0;
}
