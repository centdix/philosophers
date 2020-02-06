/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:27:44 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/05 18:27:49 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	routine_default(t_philosopher *philosopher)
{
	long	timestamp;

	while (!philosopher->is_dead)
	{
		ft_eat(philosopher, &timestamp);
		if (!philosopher->is_eating)
			while (!philosopher->is_dead && !philosopher->is_eating)
				keep_trying(philosopher, &timestamp);
		ft_sleep(philosopher, &timestamp);
		ft_think(philosopher, &timestamp);
		if (philosopher->is_dead)
		{
			write_status(timestamp, philosopher->id, DIE);
			return ;
		}
	}
}

void	*routine(void *arg)
{
	t_philosopher	*philosopher;
	long			timestamp;

	philosopher = (t_philosopher *)arg;
	if (philosopher->param.eat_times > 0)
	{
		while (philosopher->eat_times < philosopher->param.eat_times)
		{
			ft_eat(philosopher, &timestamp);
			if (!philosopher->is_eating)
				while (!philosopher->is_dead && !philosopher->is_eating)
					keep_trying(philosopher, &timestamp);
			ft_sleep(philosopher, &timestamp);
			ft_think(philosopher, &timestamp);
			if (philosopher->is_dead)
			{
				write_status(timestamp, philosopher->id, DIE);
				return (NULL);
			}
		}
	}
	else
		routine_default(philosopher);
	return (NULL);
}

int		start(t_param param)
{
	t_philosopher	*philosophers;
	int				i;
	int				ret;

	philosophers = init_ph(param);
	g_nb_forks = param.nb_philosophers;
	g_semaphore = sem_open("mysem", O_CREAT, O_RDWR, 1);
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
	sem_close(g_semaphore);
	sem_unlink("mysem");
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
