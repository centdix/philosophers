/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:03:23 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/17 22:04:14 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_status(t_shared *shared)
{
	int		i;

	i = 0;
	while (i < shared->nb_philo)
	{
		sem_wait(shared->done_philo);
		i++;
	}
	shared->glb_status = end;
	return (1);
}

void	*test_eat(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->shared->glb_status == running)
	{
		if (philo->eat_times >= philo->shared->eat_times)
		{
			philo->shared->glb_status = end;
			sem_post(philo->shared->done_philo);
			return (NULL);
		}
		usleep(5);
	}
	return (NULL);
}

void	*test_dead(void *arg)
{
	t_philo	*philo;
	int		time;
	int		i;

	philo = (t_philo *)arg;
	while (philo->shared->glb_status == running)
	{
		sem_wait(philo->action_sem);
		time = get_runtime();
		if (time - philo->last_eat > philo->shared->time_to_die)
		{
			write_status(time, philo, DEAD);
			philo->status = dead;
			philo->shared->glb_status = end;
			sem_post(philo->action_sem);
			i = -1;
			while (++i < philo->shared->nb_philo)
				sem_post(philo->shared->done_philo);
			return (NULL);
		}
		else
			sem_post(philo->action_sem);			
		usleep(5);
	}
	return (NULL);
}