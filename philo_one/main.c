#include "header.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_philo *next;

	philo = (t_philo *)arg;
	next = philo->shared->philo_lst + philo->id % philo->shared->nb_philosophers;
	while (philo->shared->glb_status == running)
	{
		ft_eat(philo, next);
		if (philo->status == eating && philo->shared->glb_status == running)
			usleep(philo->shared->time_to_eat * 1000);
		if (philo->status == eating && philo->shared->glb_status == running)
		{
			ft_sleep(philo, next);
			usleep(philo->shared->time_to_sleep * 1000);
		}
		if (philo->status == sleeping && philo->shared->glb_status == running)
			ft_think(philo);
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_shared	shared;
	int			i;

	if (init_shared(&shared, ac, av))
		return (write_err("error: argument\n"));
	get_runtime();
	init_philo(&shared);
	while (!check_dead(&shared) && !check_eat(&shared))
		usleep(1);
	i = -1;
	while (++i < shared.nb_philosophers)
		pthread_join(shared.philo_lst[i].thread, NULL);
	return (0);
}
