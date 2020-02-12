/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:54:18 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:54:21 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_eat(t_philosopher *philosopher)
{
	long			timestamp;
	long			time_since_eat;

	time_since_eat = get_timediff(philosopher->last_eat);
	timestamp = get_timediff(philosopher->param.start_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		philosopher->status = DEAD;
		write_status(timestamp, philosopher, DIE);
		exit(1);
	}
	take_forks(philosopher);
	timestamp = get_timediff(philosopher->param.start_time);
	if (philosopher->nb_forks == 2)
	{
		gettimeofday(&philosopher->last_eat, NULL);
		write_status(timestamp, philosopher, EAT);
		philosopher->status = EATING;
		philosopher->eat_times++;
		usleep(philosopher->param.time_to_eat * 1000);
		drop_forks(philosopher);
	}
}

void	ft_sleep(t_philosopher *philosopher)
{
	long			timestamp;
	long			time_since_eat;
	long			future_time;

	time_since_eat = get_timediff(philosopher->last_eat);
	timestamp = get_timediff(philosopher->param.start_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		philosopher->status = DEAD;
		write_status(timestamp, philosopher, DIE);
		exit(1);
	}
	write_status(timestamp, philosopher, SLEEP);
	philosopher->status = SLEEPING;
	future_time = time_since_eat + philosopher->param.time_to_sleep;
	if (future_time > philosopher->param.time_to_die)
	{
		usleep(1000 * (philosopher->param.time_to_die - timestamp));
		timestamp = get_timediff(philosopher->param.start_time);
		write_status(timestamp, philosopher, DIE);
		philosopher->status = DEAD;
		exit(1);
	}
	usleep(philosopher->param.time_to_sleep * 1000);
}

void	ft_think(t_philosopher *philosopher)
{
	long			timestamp;
	long			time_since_eat;

	time_since_eat = get_timediff(philosopher->last_eat);
	timestamp = get_timediff(philosopher->param.start_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		philosopher->status = DEAD;
		write_status(timestamp, philosopher, DIE);
		exit(1);
	}
	write_status(timestamp, philosopher, THINK);
	philosopher->status = THINKING;
}
