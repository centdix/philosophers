/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:03:20 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/17 22:04:03 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_eat(t_philo *philo)
{
	int		time;

	sem_wait(philo->shared->forks_sem);
	if (philo->shared->glb_status == running)
	{
		time = get_runtime();
		write_status(time, philo, EAT);
		philo->last_eat = time;
		philo->eat_times += 1;
		philo->status = eating;
	}
}

void	ft_sleep(t_philo *philo)
{
	sem_post(philo->shared->forks_sem);
	write_status(get_runtime(), philo, SLEEP);
	philo->status = sleeping;
}

void	ft_think(t_philo *philo)
{
	write_status(get_runtime(), philo, THINK);
	philo->status = thinking;
}
