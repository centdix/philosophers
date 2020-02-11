/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:50:43 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:50:57 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	routine_with_option(t_philosopher *philosopher)
{
	while (philosopher->eat_times < philosopher->param.eat_times
			&& philosopher->status != DEAD)
	{
		while (philosopher->status != DEAD && philosopher->status != EATING)
			ft_eat(philosopher);
		if (philosopher->status != DEAD)
			ft_sleep(philosopher);
		if (philosopher->status != DEAD)
			ft_think(philosopher);
	}
	return ;
}

void	*routine(void *arg)
{
	t_philosopher *philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->param.eat_times == -1)
	{
		while (philosopher->status != DEAD)
		{
			while (philosopher->status != DEAD && philosopher->status != EATING)
				ft_eat(philosopher);
			if (philosopher->status != DEAD)
				ft_sleep(philosopher);
			if (philosopher->status != DEAD)
				ft_think(philosopher);
		}
	}
	else
		routine_with_option(philosopher);
	return (NULL);
}

int		start(t_param param)
{
	t_philosopher	*philosophers;
	int				i;

	init_philosophers(&philosophers, param);
	g_nb_forks = param.nb_philosophers;
	sem_unlink("write");
	g_write_sem = sem_open("write", O_CREAT, 0666, 1);
	i = 0;
	while (i < param.nb_philosophers)
	{
		pthread_create(&philosophers[i].thread, NULL, routine,
			&philosophers[i]);
		i++;
	}
	if (param.eat_times == -1)
		wait_die(philosophers, param.nb_philosophers);
	else
		wait_eat(philosophers, param.nb_philosophers);
	sem_unlink("forks");
	sem_unlink("write");
	return (0);
}

int		main(int ac, char **av)
{
	t_param		param;

	if (ac < 5 || ac > 6)
		return (write_err("error: argument\n"));
	param.nb_philosophers = ft_atoi(av[1]);
	if (param.nb_philosophers <= 1)
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
	gettimeofday(&param.start_time, NULL);
	sem_unlink("forks");
	param.sem = sem_open("forks", O_CREAT, 0666, param.nb_philosophers / 2);
	return (start(param));
}
