#include <unistd.h>
int main() {
  char *str = "Hi there";
  str[8] = '1';
  _printstring(str, 8);
  return 0;
}
