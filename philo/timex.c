#include "philo.h"

uint64_t	timex(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	sleeper(unsigned long long to_sleep)
{
	while (timex() <= to_sleep)
		usleep(100);
}
