#include "header.h"

void    wait_die(t_philosopher *philosophers, int count)
{
    int     i;

    while (1)
    {
        i = 0;
        while (i < count)
        {
            if (philosophers[i].status == DEAD)
                return ;
            i++;
        }
    }
}

void    wait_eat(t_philosopher *philosophers, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        pthread_join(philosophers[i].thread, NULL);
        i++;
    }
}