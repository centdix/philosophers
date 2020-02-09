#include "header.h"

void    take_forks(t_philosopher *philosopher)
{
    int     index;
    int     right;
    int     left;

    index = philosopher->id - 1;
    left = index;
    right = (index + 1) % philosopher->param.nb_philosophers;
    pthread_mutex_lock(&g_mutex[ft_min(left, right)]);
    if (g_forks[ft_min(left, right)] == 1)
    {
        g_forks[ft_min(left, right)] = 0;
        philosopher->has_left = 1;
    }
    pthread_mutex_lock(&g_mutex[ft_max(left, right)]);
    if (g_forks[ft_max(left, right)] == 1)
    {
        g_forks[ft_max(left, right)] = 0;
        philosopher->has_right = 1;
    }
}

void    drop_forks(t_philosopher *philosopher)
{
    int     index;
    int     right;
    int     left;

    index = philosopher->id - 1;
    left = index;
    right = (index + 1) % philosopher->param.nb_philosophers;
    g_forks[left] = 1;
    philosopher->has_left = 0;
    pthread_mutex_unlock(&g_mutex[left]);
    g_forks[right] = 1;
    philosopher->has_right = 0;
    pthread_mutex_unlock(&g_mutex[right]);
}