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
	count = param.nb_philosophers;
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
	int		index;
	int		right;
	int		left;
	int		forks_count;

	index = philosopher->id - 1;
	forks_count = philosopher->param.nb_philosophers;
	left = index;
	right = (index == forks_count - 1) ? 0 : index + 1;
	if (forks[left] && forks[right])
		return (1);
	return (0);
}

void	take_drop_forks(int **forks, t_philosopher *philosopher, int action)
{
	int		right;
	int		left;
	int		index;
	int		forks_count;

	index = philosopher->id - 1;
	forks_count = philosopher->param.nb_philosophers;
	left = index;
	right = (index == forks_count - 1) ? 0 : index + 1;
	if (action == TAKE)
	{
		(*forks)[left] = 0;
		(*forks)[right] = 0;
	}
	if (action == DROP)
	{
		(*forks)[left] = 1;
		(*forks)[right] = 1;
	}
}
