#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_phil
{
	int				name;
	int				lfork;
	int				rfork;
	uint64_t		last;
	struct s_params	*params;
}					t_phil;

typedef struct s_params
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			num_p;
	long			num_me;
	long			eat_counter;
	uint64_t		st_time;
	t_phil			*phil;
}					t_params;

void		sleeper(unsigned long long to_sleep);
int			take_args(t_params *params, char **argv);
int			main(int argc, char **argv);
int			init_all(t_params *params);
uint64_t	timex(void);
void		free_and_end(t_params *params);
void		printer(char *s, int n, uint64_t t, t_params *p);
#endif
