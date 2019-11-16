#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	int rc = fork();

	if(rc==0)
	{
		for(int i=1; i<10000; i++)
		{
			counter_set(counter_get()+1);
		}
		printf(1, "pid : %d %d\n",getpid(), counter_get());
	}
	else
	{
		for(int i=1; i<10000; i++)
		{
			counter_set(counter_get()+1);
		}	
		printf(1, "pid : %d %d\n",getpid(), counter_get());
		wait(); 
	}
	
	
	exit();
}
