#include "header.h"

int 				nb_forks;
pthread_mutex_t		mutex;

void	*routine(void *arg)
{
	t_philosopher 	*philosopher;
	long 			timestamp;
	long			last_eat;
	struct timeval	cur_time;

	philosopher = (t_philosopher *)arg;
	while (philosopher->eat_times < philosopher->param.eat_times)
	{
		pthread_mutex_lock(&mutex);
		if (nb_forks >= 2)
		{
			philosopher->is_eating = 1;
			nb_forks -= 2;
			philosopher->eat_times++;
		}
		else
		{
			while (1)
			{
				if (nb)
			}
		}
		pthread_mutex_unlock(&mutex);
		gettimeofday(&cur_time, NULL);
		timestamp = get_timediff(philosopher->param.start_time, cur_time);
		if (timestamp > philosopher->param.time_to_die)
		{
			printf("ts: %ld / nb_%d is dead\n", timestamp, philosopher->id);
			pthread_exit(NULL);
		}
		if (philosopher->is_eating)
		{
			last_eat = timestamp;
			printf("ts: %ld / nb_%d is eating\n", timestamp, philosopher->id);
		}
		usleep(philosopher->param.time_to_eat);
		pthread_mutex_lock(&mutex);
		nb_forks += 2;
		pthread_mutex_unlock(&mutex);
		gettimeofday(&cur_time, NULL);
		timestamp = get_timediff(philosopher->param.start_time, cur_time);
		philosopher->is_sleeping = 1;
		printf("ts: %ld / nb_%d is sleeping\n", timestamp, philosopher->id);
		usleep(philosopher->param.time_to_sleep);
		gettimeofday(&cur_time, NULL);
		timestamp = get_timediff(philosopher->param.start_time, cur_time);
		philosopher->is_thinking = 1;
		printf("ts: %ld / nb_%d is thinking\n", timestamp, philosopher->id);
	}
	pthread_exit(NULL);
}

int		start(t_param param)
{
	t_philosopher	*philosophers;
	int				i;
	int 			count;
	int 			ret;

	philosophers = init_ph(param);
	ret = 0;
	i = 0;
	while (i < param.nb_philosophers)
	{
		ret = pthread_create(&philosophers[i].thread, NULL, routine, &philosophers[i]);
		if (ret)
			break ;
		i++;
	}
	count = i;
	i = 0;
	while (i < count)
	{
		ret = pthread_join(philosophers[i].thread, NULL);
		if (ret)
			break ;
		i++;
	}
	free(philosophers);
	return (ret);
}

int 	main(int ac, char **av)
{
	t_param		param;

	if (ac < 5 || ac > 6)
		return (write_err("error: argument\n"));
	param.nb_philosophers = ft_atoi(av[1]);
	if (param.nb_philosophers < 1)
		return (write_err("error: argument\n"));		
	nb_forks = param.nb_philosophers - 1;
	param.time_to_eat = ft_atoi(av[2]);
	param.time_to_die = ft_atoi(av[3]);
	param.time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		param.eat_times = -1;
	else
	{
		param.eat_times = ft_atoi(av[5]);
		if (param.eat_times <= 0)
			return (write_err("error: argument\n"));
	}
	if (gettimeofday(&param.start_time, NULL))
		return (write_err("error: time\n"));
	return (start(param));
}