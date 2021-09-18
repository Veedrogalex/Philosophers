#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_phil
{
	int				name;
	sem_t			*eat;
	int				count_eat;
	uint64_t		last;
	pid_t			pid;
	struct s_params	*params;
}					t_phil;

typedef struct s_params
{
	sem_t			*print;
	sem_t			*dead;
	sem_t			*forks;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			num_p;
	long			num_me;
	long			eat_counter;
	uint64_t		st_time;
	t_phil			*phil;
}					t_params;

void		*dead_end(void *ptr);
void		*phil_eat(void *ptr);
int			take_args(t_params *params, char **argv);
int			main(int argc, char **argv);
int			init_all(t_params *params);
uint64_t	timex(void);
void		free_and_end(t_params *params);
void		printer(char *s, int n, uint64_t t, t_params *p);
#endif
