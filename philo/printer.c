#include "philo.h"

void	printer(char *s, int n, uint64_t t, t_params *p)
{
	pthread_mutex_lock(&p->print);
	printf("%llu %d %s\n", t, n, s);
	pthread_mutex_unlock(&p->print);
}
