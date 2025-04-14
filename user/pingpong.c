#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "proc.h"

struct sleeplock ping;
struct sleeplock pong;

void
ping_process(void)
{
  for (int i = 0; i < 10; i++) {
    acquiresleep(&ping);
    printf("ping\n");
    releasesleep(&pong);
  }
  exit(0);
}

void
pong_process(void)
{
  for (int i = 0; i < 10; i++) {
    acquiresleep(&pong);
    printf("pong\n");
    releasesleep(&ping);
  }
  exit(0);
}

void
pingpong_test(void)
{
  initsleeplock(&ping, "ping");
  initsleeplock(&pong, "pong");

  acquiresleep(&ping);

  int pid1 = fork();
  if (pid1 == 0) {
    ping_process();
  }

  int pid2 = fork();
  if (pid2 == 0) {
    pong_process();
  }

  releasesleep(&ping);

  wait(0);
  wait(0);
}
