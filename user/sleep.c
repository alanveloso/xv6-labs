// Sleeping locks implementation with sleep() function

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sleeplock.h"

// Initialize a sleeplock
void
initsleeplock(struct sleeplock *lk, char *name)
{
  initlock(&lk->lk, "sleep lock");
  lk->name = name;
  lk->locked = 0;
  lk->pid = 0;
}

// Acquire a sleeplock
void
acquiresleep(struct sleeplock *lk)
{
  acquire(&lk->lk);
  while (lk->locked) {
    sleep(lk, &lk->lk); // Sleep until the lock is released
  }
  lk->locked = 1;
  lk->pid = myproc()->pid;
  release(&lk->lk);
}

// Release a sleeplock
void
releasesleep(struct sleeplock *lk)
{
  acquire(&lk->lk);
  lk->locked = 0;
  lk->pid = 0;
  wakeup(lk); // Wake up any process sleeping on this lock
  release(&lk->lk);
}

// Check if the current process holds the sleeplock
int
holdingsleep(struct sleeplock *lk)
{
  int r;
  acquire(&lk->lk);
  r = lk->locked && (lk->pid == myproc()->pid);
  release(&lk->lk);
  return r;
}

// Put current process to sleep on chan, releasing lk temporarily
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();

  acquire(&p->lock);      // Lock process state
  release(lk);            // Release the resource lock

  // Mark the process as sleeping on the channel
  p->chan = chan;
  p->state = SLEEPING;

  sched();                // Yield CPU

  // Process has been woken up
  p->chan = 0;

  release(&p->lock);      // Done modifying process state
  acquire(lk);            // Reacquire original resource lock
}
