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
		printf("%ld %d died\n", timestamp, philosopher->id);
		philosopher->is_dead = 1;
		pthread_exit(NULL);
	}
	philosopher->is_eating = 1;
	g_nb_forks -= 2;
	philosopher->last_eat = cur_time;
	philosopher->eat_times++;
	printf("%ld %d is eating\n", timestamp, philosopher->id);
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
		printf("%ld %d died\n", timestamp, philosopher->id);
		philosopher->is_dead = 1;
		pthread_exit(NULL);
	}
	philosopher->is_sleeping = 1;
	philosopher->is_eating = 0;
	printf("%ld %d is sleeping\n", timestamp, philosopher->id);
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
		printf("%ld %d died\n", timestamp, philosopher->id);
		philosopher->is_dead = 1;
		pthread_exit(NULL);
	}
	philosopher->is_thinking = 1;
	philosopher->is_sleeping = 0;
	philosopher->is_eating = 0;
	printf("%ld %d is thinking\n", timestamp, philosopher->id);
}

void	keep_trying(t_philosopher *philosopher)
{
	pthread_mutex_lock(&g_mutex);
	if (g_nb_forks >= 2)
		ft_eat(philosopher);
	pthread_mutex_unlock(&g_mutex);
	usleep(500);
}