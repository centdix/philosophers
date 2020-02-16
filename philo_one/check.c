#include "header.h"

int		check_dead(t_shared *shared)
{
	int 	i;
	int		time;
	t_philo	*current;
	t_philo *next;

	i = 0;
	while (i < shared->nb_philosophers)
	{
		current = &shared->philo_lst[i];
		next = shared->philo_lst + (current->id + 1) % shared->nb_philosophers;
		time = get_runtime();
		if (time - current->last_eat > shared->time_to_die)
		{
			write_status(time, current, DEAD);
			pthread_mutex_unlock(&current->fork.mutex);
			pthread_mutex_unlock(&next->fork.mutex);
			current->status = dead;
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