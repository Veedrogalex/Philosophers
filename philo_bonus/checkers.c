#include "philo_bonus.h"

void	*dead_end(void *ptr)
{
	t_phil	*phil;

	phil = (t_phil *)ptr;
	while (1)
	{
		if (phil->params->tt_die < (long)(timex() - phil->last))
		{
			sem_wait(phil->params->print);
			printf("%llu %d died\n", timex() - phil->params->st_time,
				phil->name);
			sem_post(phil->params->dead);
		}
		usleep(50);
	}
}
