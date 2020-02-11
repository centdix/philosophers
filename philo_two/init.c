/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:50:07 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:50:20 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		init_philosophers(t_philosopher **philosophers, t_param param)
{
	int				i;

	if (!(*philosophers = malloc(sizeof(t_philosopher)
	* param.nb_philosophers)))
		return (1);
	i = 0;
	while (i < param.nb_philosophers)
	{
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].param = param;
		(*philosophers)[i].status = -1;
		(*philosophers)[i].nb_forks = 0;
		(*philosophers)[i].eat_times = 0;
		(*philosophers)[i].last_eat = param.start_time;
		i++;
	}
	return (0);
}
