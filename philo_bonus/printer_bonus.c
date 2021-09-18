#include "philo_bonus.h"

void	printer(char *s, int n, uint64_t t, t_params *p)
{
	sem_wait(p->print);
	printf("%llu %d %s\n", t, n, s);
	sem_post(p->print);
}
