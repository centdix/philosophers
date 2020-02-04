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
		write_status(timestamp, philosopher->id, DIE);
		philosopher->is_dead = 1;
		exit(0);
	}
	philosopher->is_eating = 1;
	g_nb_forks -= 2;
	philosopher->last_eat = cur_time;
	philosopher->eat_times++;
	write_status(timestamp, philosopher->id, EAT);
	usleep(philosopher->param.time_to_eat * 1000);
	g_nb_forks += 2;
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
		write_status(timestamp, philosopher->id, DIE);
		philosopher->is_dead = 1;
		exit(0);
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
		write_status(timestamp, philosopher->id, DIE);
		philosopher->is_dead = 1;
		exit(0);
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

	sem_wait(g_semaphore);
	if (g_nb_forks >= 2)
		ft_eat(philosopher);
	sem_post(g_semaphore);
	gettimeofday(&cur_time, NULL);
	time_since_eat = get_timediff(philosopher->last_eat, cur_time);
	timestamp = get_timediff(philosopher->param.start_time, cur_time);
	if (time_since_eat > philosopher->param.time_to_die)
	{
		write_status(timestamp, philosopher->id, DIE);
		philosopher->is_dead = 1;
		exit(0);
	} 
	usleep(500);
}