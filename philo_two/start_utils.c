/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:51:17 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:51:24 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	wait_die(t_philosopher *philosophers, int count)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < count)
		{
			if (philosophers[i].status == DEAD)
				return ;
			i++;
		}
	}
}

void	wait_eat(t_philosopher *philosophers, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		pthread_join(philosophers[i].thread, NULL);
		if (philosophers[i].status == DEAD)
			return ;
		i++;
	}
}
