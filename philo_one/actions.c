#include "header.h"

int		take_forks(t_philo *philo, t_philo *next)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(&philo->fork.mutex);
	pthread_mutex_lock(&next->fork.mutex);
	if ((philo->fork.owner != philo->id && !philo->fork.used)
		&& (next->fork.owner != philo->id && !next->fork.used))
	{
		philo->fork.owner = philo->id;
		next->fork.owner = philo->id;
		philo->fork.used = 1;
		next->fork.used = 1;
		ret = 1;
	}
	pthread_mutex_unlock(&philo->fork.mutex);
	pthread_mutex_unlock(&next->fork.mutex);
	return (ret);
}

void	drop_forks(t_philo *philo, t_philo *next)
{
	pthread_mutex_lock(&philo->fork.mutex);
	pthread_mutex_lock(&next->fork.mutex);
	philo->fork.used = 0;
	next->fork.used = 0;
	pthread_mutex_unlock(&philo->fork.mutex);
	pthread_mutex_unlock(&next->fork.mutex);
}

void	ft_eat(t_philo *philo, t_philo *next)
{
	int 	time;
	int		i;

	i = 0;
	while (!take_forks(philo, next) && philo->shared->glb_status == running)
		usleep(1);
	if (philo->status != dead)
	{
		time = get_runtime();
		write_status(time, philo, EAT);
		philo->last_eat = time;
		philo->eat_times += 1;
		philo->status = eating;
	}
}

void	ft_sleep(t_philo *philo, t_philo *next)
{
	drop_forks(philo, next);
	write_status(get_runtime(), philo, SLEEP);
	philo->status = sleeping;
}

void	ft_think(t_philo *philo)
{
	write_status(get_runtime(), philo, THINK);
	philo->status = thinking;
}
