#include "types.h"
#include "stat.h"
#include "user.h"
#define LOOP 100000
#define PROCESSES 4
#define COUNT 100000

void spin_lock_time(){

	for(int j=0;j<PROCESSES;++j){
		if(fork()==0)
		{	
			int x;
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

	for(int i=0; i<PROCESSES;i++)
	{
		wait();
	}	
}

void futex_lock_time(){
	
	for(int j=0;j<PROCESSES;++j){
		if(fork()==0)
		{
			int x;
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

	for(int i=0; i<PROCESSES;i++)
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

	
	printf(1, "%d\n", t2-t1);
	printf(1, "%d\n", t4-t3);
			
	exit();
}
