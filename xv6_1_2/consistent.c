#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	counter_init();
	int rc = fork();

	int x;

	// if(rc==0)
	// {
	// 	while(1) printf(1, "%d\n", getpid());
	// }
	// else
	// {
	// 	while(1) printf(1, "%d\n", getpid());
	// }

	if(rc!=0)
	{
		
		for(int i=0; i<10000; i++)
		{
			my_lock();
			x=counter_get();
			counter_set(x+1);	
			my_unlock();
		}
	
	}
	else
	{
		for(int i=0; i<10000 ;i++)
		{
			my_lock();
			x=counter_get();
			counter_set(x+1);
			my_unlock();
		}	
	    
	}
	printf(1, "%d %d\n",getpid(), counter_get());
	wait();
	exit();
}
