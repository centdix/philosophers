#include "header.h"

void	routine_default(t_philosopher *philosopher)
{
	while (!philosopher->is_dead)
	{
		pthread_mutex_lock(&g_mutex);
		if (check_forks(g_forks, philosopher))
			ft_eat(philosopher);
		pthread_mutex_unlock(&g_mutex);
		if (!philosopher->is_eating)
			while (!philosopher->is_dead && !philosopher->is_eating)
				keep_trying(philosopher);
		ft_sleep(philosopher);
		ft_think(philosopher);
	}
}

void	*routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->param.eat_times > 0)
	{
		while (philosopher->eat_times < philosopher->param.eat_times)
		{
			pthread_mutex_lock(&g_mutex);
			if (check_forks(g_forks, philosopher))
				ft_eat(philosopher);
			pthread_mutex_unlock(&g_mutex);
			if (!philosopher->is_eating)
				while (!philosopher->is_dead && !philosopher->is_eating)
					keep_trying(philosopher);
			ft_sleep(philosopher);
			ft_think(philosopher);
		}
	}
	else
		routine_default(philosopher);
	pthread_exit(NULL);
}

int		start(t_param param)
{
	t_philosopher	*philosophers;
	int				i;
	int				ret;

	philosophers = init_ph(param);
	g_forks = init_forks(param);
	pthread_mutex_init(&g_mutex, NULL);
	ret = 0;
	i = 0;
	while (i < param.nb_philosophers)
	{
		ret = pthread_create(&philosophers[i].thread, NULL, routine,
				&philosophers[i]);
		if (ret)
			break ;
		i++;
	}
	if (param.eat_times > 0)
		wait_eat(i, philosophers);
	else
		wait_die(i, philosophers);
	free(philosophers);
	free(g_forks);
	pthread_mutex_destroy(&g_mutex);
	return (ret);
}

int		main(int ac, char **av)
{
	t_param		param;

	if (ac < 5 || ac > 6)
		return (write_err("error: argument\n"));
	param.nb_philosophers = ft_atoi(av[1]);
	if (param.nb_philosophers < 1)
		return (write_err("error: argument\n"));
	param.time_to_die = ft_atoi(av[2]);
	param.time_to_eat = ft_atoi(av[3]);
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
