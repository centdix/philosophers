/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:37:01 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/05 18:52:42 by fgoulama         ###   ########.fr       */
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
	if (check_forks(g_forks, philosopher))
	{
		philosopher->is_eating = 1;
		pthread_mutex_lock(&g_mutex);
		take_drop_forks(&g_forks, philosopher, TAKE);
		pthread_mutex_unlock(&g_mutex);
		philosopher->last_eat = cur_time;
		philosopher->eat_times++;
		write_status(*timestamp, philosopher->id, EAT);
		usleep(philosopher->param.time_to_eat * 1000);
		pthread_mutex_lock(&g_mutex);		
		take_drop_forks(&g_forks, philosopher, DROP);
		pthread_mutex_unlock(&g_mutex);
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

	if (check_forks(g_forks, philosopher))
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
