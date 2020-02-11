/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:43:11 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:43:12 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int		find_len(int n)
{
	int			len;
	long int	nb;

	len = 1;
	nb = n;
	if (nb < 0)
	{
		len++;
		nb = nb * (-1);
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int			len;
	int			stop;
	long int	nb;
	char		*result;

	len = find_len(n);
	stop = 0;
	nb = n;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (0);
	if (nb < 0)
	{
		nb = nb * (-1);
		*result = '-';
		stop = 1;
	}
	result[len] = '\0';
	while (len > stop)
	{
		result[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	return (result);
}

char			*ft_strjoin(char *str1, char *str2)
{
	int		len1;
	int		len2;
	char	*result;
	int		i;
	int		j;

	len1 = str1 ? ft_strlen(str1) : 0;
	len2 = str2 ? ft_strlen(str2) : 0;
	if (!(result = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = str1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		result[i + j] = str2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char			*ft_strdup(char *str)
{
	int		i;
	int		len;
	char	*result;

	len = str ? ft_strlen(str) : 0;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
