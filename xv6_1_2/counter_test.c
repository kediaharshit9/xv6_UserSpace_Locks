#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	counter_init();

  printf(1, "%d\n", counter_get());
  printf(1, "%d\n", counter_set(100));
  printf(1, "%d\n", counter_get());
  exit();
}
