#include "header.h"

int     init_philosophers(t_philosopher **philosophers, t_param param)
{
    int             i;

    if (!(*philosophers = malloc(sizeof(t_philosopher) * param.nb_philosophers)))
        return (1);
    i = 0;
    while (i < param.nb_philosophers)
    {
        (*philosophers)[i].id = i + 1;
        (*philosophers)[i].param = param;
        (*philosophers)[i].status = -1;
        (*philosophers)[i].has_left = 0;
        (*philosophers)[i].has_right = 0;

        (*philosophers)[i].eat_times = 0;
        (*philosophers)[i].last_eat = param.start_time;
        i++;
    }
    return (0);
}

int     init_mutex(pthread_mutex_t **g_mutex, int count)
{
    int i;

    if (!(*g_mutex = malloc(sizeof(pthread_mutex_t) * count)))
        return (1);
    i = 0;
    while (i < count)
    {
        pthread_mutex_init(&(*g_mutex)[i], NULL);
        i++;
    }
    return (0);
}

int     init_forks(int **g_forks, int count)
{
    int     i;

    if (!(*g_forks = malloc(sizeof(int) * count)))
        return (1);
    i = 0;
    while (i < count)
    {
        (*g_forks)[i] = 1;
        i++;
    }
    return (0);
}
