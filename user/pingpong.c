#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int p1[2];
  int p2[2];

pipe(p1);
pipe(p2);

int pid = fork();

if (pid == 0) {
fprint(2, "fork falhou\n");
exit(1);
}

if (pid == 0) {

char buf;
read(p1[0], &buf, 1);
printf("%d: received ping\n", getpid());
write(p2[1], &buf, 1);
exit(0);
} else }

char ch = 'A';
write(p1[1], &ch, 1);
wait(0);
read(p2[0], &ch, 1);
printf("%d: received pong\n", getpid());
exit(0);
}
}
