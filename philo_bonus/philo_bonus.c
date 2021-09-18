#include "philo_bonus.h"

void	*phil_eat(void *ptr)
{
	int			i;
	t_params	*params;

	params = (t_params *)ptr;
	i = -1;
	while (++i < params->num_p)
		sem_wait(params->phil[i].eat);
	sem_wait(params->print);
	printf("banquet is over\n");
	sem_post(params->dead);
	return (NULL);
}

static void	forks(t_phil *phil)
{
	sem_wait(phil->params->forks);
	printer("has taken a fork",
		phil->name, timex() - phil->params->st_time, phil->params);
	sem_wait(phil->params->forks);
	printer("has taken a fork",
		phil->name, timex() - phil->params->st_time, phil->params);
	printer("is eating",
		phil->name, timex() - phil->params->st_time, phil->params);
	phil->count_eat++;
	if (phil->count_eat == phil->params->num_me)
		sem_post(phil->eat);
	phil->last = timex();
	usleep(phil->params->tt_eat * 1000);
	sem_post(phil->params->forks);
	sem_post(phil->params->forks);
}

static void	actions(t_phil *ph)
{
	uint64_t	dif;
	pthread_t	checker;

	pthread_create(&checker, NULL, dead_end, ph);
	pthread_detach(checker);
	if (ph->name % 2)
		usleep(100);
	while (1)
	{
		forks(ph);
		dif = timex() - ph->params->st_time;
		printer("is sleeping", ph->name, dif, ph->params);
		usleep(ph->params->tt_sleep * 1000);
		dif = timex() - ph->params->st_time;
		printer("is thinking", ph->name, dif, ph->params);
	}
}

int	banquet_begin(t_params *params)
{
	int			i;
	pthread_t	eater;

	eater = NULL;
	init_all(params);
	i = -1;
	while (++i < params->num_p)
	{
		params->phil[i].pid = fork();
		if (params->phil[i].pid < 0)
			free_and_end(params);
		if (params->phil[i].pid == 0)
			actions(&params->phil[i]);
	}
	pthread_create(&eater, NULL, phil_eat, params);
	pthread_detach(eater);
	sem_wait(params->dead);
	exit (0);
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
