#include "types.h"
#include "stat.h"
#include "user.h"
#define LOOP 10000
#define CHILD 3
#define COUNT 100000

void spin_lock_time(){
	int x;
	for(int j=0;j<CHILD;++j){
		if(fork()==0)
		{	
			for(int i=0; i<LOOP; i++)
			{
				my_lock_spin();
				x=counter_get();
				counter_set(x+1);	
				my_unlock();
			}
			exit();
		}
	}

	//inside parent
	for(int i=0; i<LOOP; i++)
	{
		my_lock_spin();
		x=counter_get();
		counter_set(x+1);	
		my_unlock();
	}

	for(int i=0; i<CHILD;i++)
	{
		wait();
	}	
}

void futex_lock_time(){
	int x;
	for(int j=0;j<CHILD;++j){
		if(fork()==0)
		{
			for(int i=0; i<LOOP; i++)
			{
				my_lock_futex(COUNT);
				x=counter_get();
				counter_set(x+1);	
				my_unlock();
			}
			exit();
		}
	}

	//inside parent
	for(int i=0; i<LOOP; i++)
	{
		my_lock_futex(COUNT);
		x=counter_get();
		counter_set(x+1);	
		my_unlock();
	}

	for(int i=0; i<CHILD;i++)
	{
		wait();
	}	
}

int
main(int argc, char *argv[])
{
	counter_init();
	int t1=uptime();
	spin_lock_time();
	int t2=uptime();

	counter_init();
	int t3=uptime();
	futex_lock_time();
	int t4=uptime();

	
	printf(1, "spin lock ticks  : %d\n", t2-t1);
	printf(1, "futex lock ticks : %d\n", t4-t3);
			
	exit();
}
