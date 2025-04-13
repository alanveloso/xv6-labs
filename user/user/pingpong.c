#include "types.h"
#include "riscv.h"
#include "user.h"

int
main() {
  int p2c[2]; // Pipe do pai para o filho
  int c2p[2]; // Pipe do filho para o pai

  pipe(p2c);
  pipe(c2p);

  int pid = fork();

  if (pid < 0) {
    fprintf(2, "Erro ao criar processo\n");
    exit(1);
  }

  if (pid == 0) {
    // Processo filho
    char buf;
    read(p2c[0], &buf, 1); // Lê byte do pai
    printf("%d: received ping\n", getpid());
    write(c2p[1], &buf, 1); // Envia byte de volta
    exit(0);
  } else {
    // Processo pai
    char byte = 'A';
    write(p2c[1], &byte, 1); // Envia byte ao filho
    wait(0); // Aguarda o filho terminar

    char buf;
    read(c2p[0], &buf, 1); // Lê resposta do filho
    printf("%d: received pong\n", getpid());
    exit(0);
  }
}
