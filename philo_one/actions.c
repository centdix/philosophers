#include "header.h"

int		take_forks(t_philo *philo)
{
	int		index;
	int		left;
	int		right;

	index = philo->id - 1;
	left = index;
	right = (index + 1) % philo->shared->nb_philosophers;
	pthread_mutex_lock(&g_mutex[ft_min(left, right)]);
	if (g_forks[ft_min(left, right)] == 1)
		g_forks[ft_min(left, right)] = 0;
	pthread_mutex_lock(&g_mutex[ft_max(left, right)]);
	if (g_forks[ft_max(left, right)] == 1)
		g_forks[ft_max(left, right)] = 0;
	return (0);
}

int		drop_forks(t_philo *philo)
{
	int		index;
	int		left;
	int		right;

	index = philo->id - 1;
	left = index;
	right = (index + 1) % philo->shared->nb_philosophers;
	g_forks[left] = 1;
	pthread_mutex_unlock(&g_mutex[left]);
	g_forks[right] = 1;
	pthread_mutex_unlock(&g_mutex[right]);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	int 	time;

	take_forks(philo);
	time = get_runtime();
	write_status(time, philo->id, EAT);
	philo->last_eat = time;
	philo->eat_times += 1;
	philo->status = eating;
}

void	ft_sleep(t_philo *philo)
{
	drop_forks(philo);
	write_status(get_runtime(), philo->id, SLEEP);
	philo->status = sleeping;
}

void	ft_think(t_philo *philo)
{
	write_status(get_runtime(), philo->id, THINK);
	philo->status = thinking;
}
