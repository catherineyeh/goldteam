#include <types.h>
#include <lib.h>
#include <array.h>
#include <test.h>

#define TESTSIZE 73

static
void
testa(struct array *a)
{
  kprintf("Beginning printchar test...\n");

  printchar("a");

  kprintf("printchar test complete\n");
  	return 0;
}
