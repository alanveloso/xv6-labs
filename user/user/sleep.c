#include "types.h"
#include "riscv.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Uso: sleep <ticks>\n");
    exit(1);
  }

  int ticks = atoi(argv[1]);
  if (ticks < 0) {
    fprintf(2, "sleep: número de ticks inválido\n");
    exit(1);
  }

  sleep(ticks);
  exit(0);
}
