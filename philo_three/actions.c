/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:38:49 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/05 19:03:47 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_eat(t_philosopher *philosopher, long *timestamp)
{
	struct timeval	cur_time;
	long			time_since_eat;

	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	*timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		philosopher->is_dead = 1;
		return ;
	}
	if (g_nb_forks >= 2)
	{
		philosopher->is_eating = 1;
		sem_wait(g_semaphore);
		g_nb_forks -= 2;
		sem_post(g_semaphore);
		philosopher->last_eat = cur_time;
		philosopher->eat_times++;
		write_status(*timestamp, philosopher->id, EAT);
		usleep(philosopher->param.time_to_eat * 1000);
		sem_wait(g_semaphore);
		g_nb_forks += 2;
		sem_post(g_semaphore);
	}
}

void	ft_sleep(t_philosopher *philosopher, long *timestamp)
{
	struct timeval	cur_time;
	long			time_since_eat;

	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	*timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		philosopher->is_dead = 1;
		return ;
	}
	philosopher->is_sleeping = 1;
	philosopher->is_eating = 0;
	write_status(*timestamp, philosopher->id, SLEEP);
	usleep(philosopher->param.time_to_sleep * 1000);
}

void	ft_think(t_philosopher *philosopher, long *timestamp)
{
	struct timeval	cur_time;
	long			time_since_eat;

	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	*timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		philosopher->is_dead = 1;
		return ;
	}
	philosopher->is_thinking = 1;
	philosopher->is_sleeping = 0;
	philosopher->is_eating = 0;
	write_status(*timestamp, philosopher->id, THINK);
}

void	keep_trying(t_philosopher *philosopher, long *timestamp)
{
	struct timeval	cur_time;
	long			time_since_eat;

	if (g_nb_forks >= 2)
		ft_eat(philosopher, timestamp);
	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	*timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		philosopher->is_dead = 1;
		return ;
	}
	usleep(50);
}
