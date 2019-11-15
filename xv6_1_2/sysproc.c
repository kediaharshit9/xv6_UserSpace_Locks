#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"



int count;
uint count_lock;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_counter_init(void)
{ 
  count = 0;
  initmylock(&count_lock);
  return 1;
}


int
sys_counter_get(void)
{
  return count;
}

int
sys_counter_set(void)
{
  int n;
  argint(0, &n);
  count = n;
  return 1;
}

int
sys_my_lock_spin(void)
{
  spinacquire(&count_lock);
  return 0;
}

int
sys_my_lock_futex(void)
{
  int n;
  argint(0, &n);
  futexacquire(&count_lock,n);
  return 0;
}

int
sys_my_unlock(void)
{
  myrelease(&count_lock);
  return 0;
}