/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:03:36 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/17 22:03:38 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_create(&philo->eat_thread, NULL, test_eat, philo);
	pthread_create(&philo->dead_thread, NULL, test_dead, philo);
	while (philo->shared->glb_status == running)
	{
		ft_eat(philo);
		if (philo->status == eating && philo->shared->glb_status == running)
			usleep(philo->shared->time_to_eat * 1000);
		if (philo->status == eating && philo->shared->glb_status == running)
		{
			ft_sleep(philo);
			usleep(philo->shared->time_to_sleep * 1000);
		}
		if (philo->status == sleeping && philo->shared->glb_status == running)
			ft_think(philo);
	}
	pthread_join(philo->eat_thread, NULL);
	pthread_join(philo->dead_thread, NULL);
	return (NULL);
}

int		main(int ac, char **av)
{
	t_shared	shared;

	if (init_shared(&shared, ac, av))
		return (write_err("error: argument\n"));
	get_runtime();
	init_philo(&shared);
	check_status(&shared);
	sem_unlink("write");
	sem_unlink("forks");
	sem_unlink("action");
	sem_unlink("done_philo");
	return (0);
}
