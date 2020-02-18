/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:54:36 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:54:41 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	take_forks(t_philosopher *philosopher)
{
	long			timestamp;
	long			time_since_eat;

	sem_wait(philosopher->param.sem);
	time_since_eat = get_timediff(philosopher->last_eat);
	timestamp = get_timediff(philosopher->param.start_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		philosopher->status = DEAD;
		write_status(timestamp, philosopher, DIE);
		exit(1);
	}
	if (g_nb_forks >= 2)
	{
		g_nb_forks -= 2;
		philosopher->nb_forks += 2;
	}
	else
		sem_post(philosopher->param.sem);
}

void	drop_forks(t_philosopher *philosopher)
{
	g_nb_forks += 2;
	philosopher->nb_forks -= 2;
	sem_post(philosopher->param.sem);
}
