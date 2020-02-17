/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 21:58:41 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/17 22:00:21 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_dead(t_shared *shared)
{
	int		i;
	int		time;
	t_philo	*current;
	t_philo *next;

	i = 0;
	while (i < shared->nb_philo)
	{
		current = &shared->philo_lst[i];
		next = shared->philo_lst + current->id % shared->nb_philo;
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
	while (i < shared->nb_philo)
	{
		if (shared->philo_lst[i].eat_times < shared->eat_times)
			return (0);
		i++;
	}
	shared->glb_status = end;
	return (1);
}
