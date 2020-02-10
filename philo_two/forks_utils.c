#include "header.h"

void    take_forks(t_philosopher *philosopher)
{
    sem_wait(g_semaphore);
    if (g_nb_forks >= 2 && philosopher->nb_forks == 0)
    {
        g_nb_forks -= 2;
        philosopher->nb_forks += 2;
    }
    sem_post(g_semaphore);
}

void    drop_forks(t_philosopher *philosopher)
{
    sem_wait(g_semaphore);
    g_nb_forks += 2;
    philosopher->nb_forks -= 2;
    sem_post(g_semaphore);
}