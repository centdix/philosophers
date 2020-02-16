#include "header.h"

unsigned long	get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

int				get_runtime()
{
	static unsigned long	start = 0;

	if (!start)
		start = get_time();
	return ((get_time() - start) / 1000);
}