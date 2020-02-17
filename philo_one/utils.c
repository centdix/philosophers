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