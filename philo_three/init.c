/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:03:33 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/17 22:04:57 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_sem(t_shared *shared)
{
	sem_unlink("write");
	sem_unlink("forks");
	sem_unlink("done_philo");
	sem_unlink("end");
	shared->write_sem = sem_open("write", O_CREAT, 0666, 1);
	shared->forks_sem = sem_open("forks", O_CREAT, 0666, shared->nb_philo / 2);
	shared->done_philo = sem_open("done_philo", O_CREAT, 0666, 0);
	shared->end_sem = sem_open("end", O_CREAT, 0666, 0);
}

int		init_shared(t_shared *shared, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (1);
	shared->nb_philo = ft_atoi(av[1]);
	if (shared->nb_philo <= 1 || shared->nb_philo > MAX_PHILO)
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
	init_sem(shared);
	return (0);
}

int		init_philo(t_shared *shared)
{
	int		i;
	t_philo	philo;

	i = 0;
	while (i < shared->nb_philo)
	{
		philo.id = i + 1;
		philo.status = running;
		philo.eat_times = 0;
		philo.last_eat = 0;
		philo.shared = shared;
		sem_unlink("action");
		philo.action_sem = sem_open("action", O_CREAT, 0666, 1);
		if (!fork())
		{
			routine(&philo);
			exit(0);
		}
		i++;
	}
	return (0);
}
