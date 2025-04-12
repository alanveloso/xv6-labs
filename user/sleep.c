#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sleeplock.h"

void
initsleeplock(struct sleeplock *lk, char *name)
{
  initlock(&lk->lk, "sleep lock");
  lk->name = name;
  lk->locked = 0;
  lk->pid = 0;
}

void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();
  
  // Libera o spinlock passado, se houver.
  if (lk != 0) {
    release(lk);
  }

  // Coloca o processo para dormir.
  acquire(&p->lock);
  p->chan = chan;
  p->state = SLEEPING;
  sched();

  // Após acordar, limpa o canal e libera o lock do processo.
  p->chan = 0;
  release(&p->lock);

  // Reacquire o spinlock original, se passado.
  if (lk != 0) {
    acquire(lk);
  }
}

void
acquiresleep(struct sleeplock *lk)
{
  acquire(&lk->lk);
  while (lk->locked) {
    sleep(lk, &lk->lk);
  }
  lk->locked = 1;
  lk->pid = myproc()->pid;
  release(&lk->lk);
}

void
releasesleep(struct sleeplock *lk)
{
  acquire(&lk->lk);
  lk->locked = 0;
  lk->pid = 0;
  wakeup(lk);
  release(&lk->lk);
}

int
holdingsleep(struct sleeplock *lk)
{
  int r;
  
  acquire(&lk->lk);
  r = lk->locked && (lk->pid == myproc()->pid);
  release(&lk->lk);
  return r;
}
