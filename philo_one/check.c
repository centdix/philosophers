#include "header.h"

int		check_dead(t_shared *shared)
{
	int i;
	int	time;

	i = 0;
	while (i < shared->nb_philosophers)
	{
		time = get_runtime();
		if (time - shared->philo_lst[i].last_eat > shared->time_to_die)
		{
			write_status(time, shared->philo_lst[i].id, DEAD);
			shared->glb_status = end;
			return (1);
		}
		i++;
	}
	return (0);
}

int		check_eat(t_shared *shared)
{
	int		i;

	if (shared->eat_times == -1)
		return (0);
	i = 0;
	while (i < shared->nb_philosophers)
	{
		if (shared->philo_lst[i].eat_times < shared->eat_times)
			return (0);
		i++;
	}
	shared->glb_status = end;
	return (1);
}