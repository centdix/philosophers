#include "header.h"

int		init_shared(t_shared *shared, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (1);
	shared->nb_philosophers = ft_atoi(av[1]);
	if (shared->nb_philosophers <= 1)
		return (1);
	shared->time_to_die = ft_atoi(av[2]);
	shared->time_to_eat = ft_atoi(av[3]);
	shared->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		shared->eat_times = -1;
	else
	{
		shared->eat_times = ft_atoi(av[5]);
		if (shared->eat_times <= 0)
			return (1);
	}
	shared->glb_status = running;
	pthread_mutex_init(&shared->write_mutex, NULL);
	return (0);
}

void	init_fork(t_fork *fork)
{
	fork->owner = -1;
	fork->used = 0;
	pthread_mutex_init(&fork->mutex, NULL);
}

int		init_philo(t_shared *shared)
{
	int 	i;

	i = 0;
	while (i < shared->nb_philosophers)
	{
		shared->philo_lst[i].id = i + 1;
		shared->philo_lst[i].status = running;
		shared->philo_lst[i].eat_times = 0;
		shared->philo_lst[i].last_eat = 0;
		init_fork(&shared->philo_lst[i].fork);
		shared->philo_lst[i].shared = shared;
		pthread_create(&shared->philo_lst[i].thread, NULL, routine,
			&shared->philo_lst[i]);
		i++;
	}
	return (0);
}
