/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:55:58 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:56:03 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int				ft_atoi(char *str)
{
	int		nb;
	int		signe;

	nb = 0;
	signe = 1;
	while (*str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb * signe);
}

int				ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int				ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

long			get_timediff(struct timeval start)
{
	struct timeval	cur_time;
	long			result;
	int				micro;

	gettimeofday(&cur_time, NULL);
	result = cur_time.tv_sec - start.tv_sec;
	result *= 1000;
	micro = cur_time.tv_usec - start.tv_usec;
	micro /= 1000;
	result += micro;
	return (result);
}
