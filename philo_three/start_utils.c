/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:39:41 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/05 19:06:44 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	wait_eat(int count, t_philosopher *philosophers)
{
	int i;

	i = 0;
	while (i < count)
	{
		waitpid(philosophers[i].pid, NULL, 0);
		i++;
	}
}

void	kill_all(int count, t_philosopher *philosophers)
{
	int i;

	i = 0;
	while (i < count)
	{
		kill(philosophers[i].pid, SIGKILL);
		i++;
	}
}

void	wait_die(int count, t_philosopher *philosophers)
{
	int i;
	int ret;

	while (1)
	{
		i = 0;
		while (i < count)
		{
			ret = waitpid(philosophers[i].pid, NULL, WNOHANG);
			if (ret > 0)
			{
				kill_all(count, philosophers);
				return ;
			}
			i++;
		}
	}
}
