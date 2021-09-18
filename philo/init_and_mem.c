#include "philo.h"

static int	init_banquet(t_params *params)
{
	int	i;

	i = -1;
	params->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * params->num_p);
	if (params->forks == NULL)
		return (0);
	while (++i < params->num_p)
		if (pthread_mutex_init(&params->forks[i], NULL))
			return (0);
	if (pthread_mutex_init(&params->print, NULL))
		return (0);
	return (1);
}

static void	init_philosoph(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->num_p)
	{
		params->phil[i].name = i + 1;
		params->phil[i].lfork = i;
		params->phil[i].rfork = i + 1;
		if (i == params->num_p - 1)
			params->phil[i].rfork = 0;
		params->phil[i].params = params;
	}
}

int	init_all(t_params *params)
{
	if (!init_banquet(params))
		return (0);
	init_philosoph(params);
	return (1);
}

void	free_and_end(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->num_p)
		pthread_mutex_destroy(&params->forks[i]);
	free(params->forks);
	if (params->phil)
		free(params->phil);
	exit(0);
}
