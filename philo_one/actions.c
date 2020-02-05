#include "header.h"

void	ft_eat(t_philosopher *philosopher)
{
	struct timeval	cur_time;
	long			timestamp;
	long			time_since_eat;

	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		if (!philosopher->is_dead)
			write_status(timestamp, philosopher->id, DIE);
		philosopher->is_dead = 1;
		return ;
	}
	philosopher->is_eating = 1;
	take_drop_forks(g_forks, philosopher, TAKE);
	philosopher->last_eat = cur_time;
	philosopher->eat_times++;
	write_status(timestamp, philosopher->id, EAT);
	usleep(philosopher->param.time_to_eat * 1000);
	take_drop_forks(g_forks, philosopher, DROP);
}

void	ft_sleep(t_philosopher *philosopher)
{
	struct timeval	cur_time;
	long			timestamp;
	long			time_since_eat;

	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		if (!philosopher->is_dead)
			write_status(timestamp, philosopher->id, DIE);
		philosopher->is_dead = 1;
		return ;
	}
	philosopher->is_sleeping = 1;
	philosopher->is_eating = 0;
	write_status(timestamp, philosopher->id, SLEEP);
	usleep(philosopher->param.time_to_sleep * 1000);
}

void	ft_think(t_philosopher *philosopher)
{
	struct timeval	cur_time;
	long			timestamp;
	long			time_since_eat;

	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		if (!philosopher->is_dead)
			write_status(timestamp, philosopher->id, DIE);
		philosopher->is_dead = 1;
		return ;
	}
	philosopher->is_thinking = 1;
	philosopher->is_sleeping = 0;
	philosopher->is_eating = 0;
	write_status(timestamp, philosopher->id, THINK);
}

void	keep_trying(t_philosopher *philosopher)
{
	struct timeval	cur_time;
	long			time_since_eat;
	long			timestamp;

	pthread_mutex_lock(&g_mutex);
	if (check_forks(g_forks, philosopher))
		ft_eat(philosopher);
	pthread_mutex_unlock(&g_mutex);
	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		if (!philosopher->is_dead)
			write_status(timestamp, philosopher->id, DIE);
		philosopher->is_dead = 1;
		return ;
	} 
	usleep(500);
}