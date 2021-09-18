#include "philo.h"

static void	forks(t_phil *phil)
{
	pthread_mutex_lock(&phil->params->forks[phil->lfork]);
	printer("has taken a fork",
		phil->name, timex() - phil->params->st_time, phil->params);
	pthread_mutex_lock(&phil->params->forks[phil->rfork]);
	phil->params->eat_counter++;
	phil->last = timex();
	printer("has taken a fork",
		phil->name, timex() - phil->params->st_time, phil->params);
	printer("is eating",
		phil->name, timex() - phil->params->st_time, phil->params);
	sleeper(phil->params->tt_eat + timex());
	pthread_mutex_unlock(&phil->params->forks[phil->rfork]);
	pthread_mutex_unlock(&phil->params->forks[phil->lfork]);
}

static void	*actions(void *ptr)
{
	t_phil		*ph;
	uint64_t	dif;

	ph = (t_phil *)ptr;
	if (!(ph->name % 2))
		usleep(100);
	while (1)
	{
		forks(ph);
		dif = timex() - ph->params->st_time;
		printer("is sleeping", ph->name, dif, ph->params);
		sleeper(ph->params->tt_sleep + timex());
		dif = timex() - ph->params->st_time;
		printer("is thinking", ph->name, dif, ph->params);
	}
}

static void	dead_end(t_params *params)
{
	long	i;

	while (1)
	{
		i = -1;
		while (++i < params->num_p)
		{
			if (params->tt_die < (long)(timex() - params->phil[i].last))
			{
				pthread_mutex_lock(&params->print);
				printf("%llu %d died\n",
					timex() - params->st_time, params->phil[i].name);
				free_and_end(params);
			}
			if (params->num_me && (params->eat_counter
					% (params->num_me * params->num_p)) == 0
				&& params->eat_counter != 0)
			{
				pthread_mutex_lock(&params->print);
				printf("banquet is over\n");
				free_and_end(params);
			}
		}
		usleep(50);
	}
}

int	banquet_begin(t_params *params)
{
	int			i;
	pthread_t	threads;

	params->phil = (t_phil *)malloc(sizeof(t_phil *) * params->num_p);
	if (!params->phil)
		return (0);
	init_all(params);
	params->st_time = timex();
	i = -1;
	while (++i < params->num_p)
	{
		params->phil[i].last = timex();
		if (pthread_create(&threads, NULL, actions, &params->phil[i]))
			return (0);
		pthread_detach(threads);
	}
	dead_end(params);
	return (1);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arg's\n"));
	if (!take_args(&params, argv))
		return (printf("Wrong params\n"));
	if (!banquet_begin(&params))
		return (printf("Banquet fail\n"));
	return (0);
}
