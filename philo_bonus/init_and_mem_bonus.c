#include "philo_bonus.h"

static int	init_banquet(t_params *params)
{
	sem_unlink("dead");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("eat");
	params->dead = sem_open("dead", O_CREAT, 0777, 0);
	params->print = sem_open("print", O_CREAT, 0777, 1);
	params->forks = sem_open("forks", O_CREAT, 0777, params->num_p);
	if (params->dead == SEM_FAILED || params->print == SEM_FAILED
		|| params->forks == SEM_FAILED)
		return (0);
	return (1);
}

static int	init_philosoph(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->num_p)
	{
		params->phil[i].name = i + 1;
		params->phil[i].eat = sem_open("eat", O_CREAT, 0777, 0);
		if (params->phil[i].eat == SEM_FAILED)
			return (0);
		params->phil[i].last = timex();
		params->phil[i].count_eat = 0;
		params->phil[i].params = params;
	}
	return (1);
}

int	init_all(t_params *params)
{
	params->st_time = timex();
	params->phil = (t_phil *)malloc(sizeof(t_phil) * params->num_p);
	if (!params->phil)
		return (0);
	if (!init_banquet(params))
		return (0);
	if (!init_philosoph(params))
		return (0);
	return (1);
}

void	free_and_end(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->num_p)
		kill(params->phil[i].pid, SIGKILL);
	if (params->phil)
		free(params->phil);
	sem_unlink("eat");
	sem_unlink("dead");
	sem_unlink("forks");
	sem_unlink("print");
	exit(33);
}
