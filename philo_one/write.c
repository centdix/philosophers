#include "header.h"

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr(int nb)
{
	char	c;

	if (nb / 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	write_status(int timestamp, int id, int action)
{
	pthread_mutex_lock(&g_write_mutex);
	ft_putnbr(timestamp);
	ft_putstr(" ");
	ft_putnbr(id);
	ft_putstr(" ");
	if (action == EAT)
		ft_putstr("is eating\n");
	else if (action == SLEEP)
		ft_putstr("is sleeping\n");
	else if (action == THINK)
		ft_putstr("is thinking\n");
	else if (action == DEAD)
		ft_putstr("is dead\n");
	pthread_mutex_unlock(&g_write_mutex);
}

int		write_err(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}