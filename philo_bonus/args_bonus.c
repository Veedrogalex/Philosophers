#include "philo_bonus.h"

static long	ft_atoi(const char *str)
{
	long	nbr;
	int		flag;
	char	*s;

	s = (char *)str;
	nbr = 0;
	flag = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
	{
		s++;
		flag = -1;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		nbr = nbr * 10 + (*s - '0');
		s++;
	}
	return (nbr * flag);
}

int	take_args(t_params *params, char **argv)
{
	params->num_p = ft_atoi(argv[1]);
	params->tt_die = ft_atoi(argv[2]);
	params->tt_eat = ft_atoi(argv[3]);
	params->tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		params->num_me = ft_atoi(argv[5]);
	else
		params->num_me = 0;
	if ((params->num_p < 1 && params->num_p > 200) || params->tt_die < 60
		|| params->tt_eat < 60 || params->tt_sleep < 60)
		return (0);
	return (1);
}
