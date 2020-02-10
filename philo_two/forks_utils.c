#include "header.h"

void    take_forks(t_philosopher *philosopher)
{
    sem_wait(philosopher->param.sem);
    if (g_nb_forks >= 2)
    {
        g_nb_forks -= 2;
        philosopher->nb_forks += 2;
    }
    else
        sem_post(philosopher->param.sem);
}

void    drop_forks(t_philosopher *philosopher)
{
    g_nb_forks += 2;
    philosopher->nb_forks -= 2;
    sem_post(philosopher->param.sem);
}