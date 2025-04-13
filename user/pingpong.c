#include "kernel/types.h"
#include "user/user.h"

int main() {
  int ping[2];               // comeca pelo infeliz do ping para pong
  int pong[2];               // dps do pongo para o ping e vice versa
  char buf[1];

  pipe(ping);
  pipe(pong);

  int pid = fork();

  if (pid < 0) {
    fprintf(2, "fork failed\n");
    exit(1);
  }

  if (pid == 0) {
                            // Processo do pong
    read(ping[0], buf, 1);
    printf("%d: received ping\n", getpid());
    write(pong[1], buf, 1);
    close(ping[0]);
    close(ping[1]);
    close(pong[0]);
    close(pong[1]);
    exit(0);
  } else {
                            // Processo do ping
    write(ping[1], "A", 1);
    read(pong[0], buf, 1);
    printf("%d: received pong\n", getpid());
    close(ping[0]);
    close(ping[1]);
    close(pong[0]);
    close(pong[1]);
    wait(0);                 // agora tem que esperar o pong termninar, eu espero.. 
    exit(0);
  }
}
