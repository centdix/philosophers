#include "header.h"

int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			write_err(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int 		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			ft_atoi(char *str)
{
	int		nb;
	int		signe;

	nb = 0;
	signe = 1;
	while (*str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb * signe);
}

t_philosopher	*init_ph(t_param param)
{
	t_philosopher 	*philosophers;
	int 			i;

	if (!(philosophers = malloc(sizeof(t_philosopher) * param.nb_philosophers)))
		return (NULL);
	i = 0;
	while (i < param.nb_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].param = param;
		philosophers[i].is_eating = 0;
		philosophers[i].is_sleeping = 0;
		philosophers[i].is_dead = 0;
		philosophers[i].eat_times = 0;
		philosophers[i].last_eat = param.start_time;
		i++;
	}
	return (philosophers);
}

long			get_timediff(struct timeval start, struct timeval now)
{
	long	result;
	int 	micro;

	result = now.tv_sec - start.tv_sec;
	result *= 1000;
	micro = now.tv_usec - start.tv_usec;
	micro /= 1000;
	result += micro;
	return (result);
}