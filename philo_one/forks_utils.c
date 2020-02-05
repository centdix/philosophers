/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:37:08 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/05 18:53:14 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		*init_forks(t_param param)
{
	int		i;
	int		count;
	int		*forks;

	i = 0;
	count = param.nb_philosophers - 1;
	if (!(forks = malloc(sizeof(int) * count)))
		return (NULL);
	while (i < count)
	{
		forks[i] = 1;
		i++;
	}
	return (forks);
}

int		check_forks(int *forks, t_philosopher *philosopher)
{
	int		ph_index;
	int		next;
	int		prev;
	int		forks_count;

	ph_index = philosopher->id - 1;
	forks_count = philosopher->param.nb_philosophers - 1;
	prev = (ph_index == 0) ? forks_count - 1 : ph_index - 1;
	next = (ph_index == forks_count) ? 0 : ph_index + 1;
	if (forks[prev] && forks[next])
		return (1);
	return (0);
}

void	take_drop_forks(int *forks, t_philosopher *philosopher, int action)
{
	int		next;
	int		prev;
	int		ph_index;
	int		forks_count;

	ph_index = philosopher->id - 1;
	forks_count = philosopher->param.nb_philosophers - 1;
	prev = (ph_index == 0) ? forks_count - 1 : ph_index - 1;
	next = (ph_index == forks_count - 1) ? 0 : ph_index + 1;
	if (action == TAKE)
	{
		forks[prev] = 0;
		forks[next] = 0;
	}
	if (action == DROP)
	{
		forks[prev] = 1;
		forks[next] = 1;
	}
}
