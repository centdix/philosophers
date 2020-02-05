/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:38:11 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/05 18:58:30 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	wait_eat(int count, t_philosopher *philosophers)
{
	int i;
	int ret;

	i = 0;
	while (i < count)
	{
		ret = pthread_join(philosophers[i].thread, NULL);
		if (ret)
			break ;
		i++;
	}
}

void	wait_die(int count, t_philosopher *philosophers)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < count)
		{
			if (philosophers[i].is_dead)
				return ;
			i++;
		}
	}
}
