#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	counter_init();
	int x;
	if(fork()==0)
	{
		for(int i=0; i<10000; i++)
		{
			my_lock_futex(10000);
			x=counter_get();
			counter_set(x+1);	
			my_unlock();
		}
		printf(1, "%d %d\n",getpid(), counter_get());
	}
	else
	{		
		for(int i=0; i<10000;i++)
		{
			my_lock_futex(10000);
			x=counter_get();
			counter_set(x+1);	
			my_unlock();
		}	
		printf(1, "%d %d\n",getpid(), counter_get());
		wait();

	}
	exit();
}

