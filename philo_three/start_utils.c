/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:55:39 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:55:43 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	kill_all(t_philosopher *philosophers, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		kill(philosophers[i].pid, SIGKILL);
		i++;
	}
}

void	wait_die(t_philosopher *philosophers, int count)
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
				kill_all(philosophers, count);
				return ;
			}
			i++;
		}
	}
}

void	wait_eat(t_philosopher *philosophers, int count)
{
	int i;
	int status;

	i = 0;
	while (i < count)
	{
		waitpid(philosophers[i].pid, &status, 0);
		if (status != 0)
		{
			kill_all(philosophers, count);
			return ;
		}
		i++;
	}
}
