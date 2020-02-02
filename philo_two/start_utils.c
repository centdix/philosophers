#include "header.h"

void    wait_eat(int count, t_philosopher *philosophers)
{
    int i;
    int ret;

    i = 0;
    while (i < count)
    {
     ret = pthread_join(philosophers[i].thread, NULL);
     if (ret)
         break ;
     i++;
    }
}

void    wait_die(int count, t_philosopher *philosophers)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < count)
        {
            if (philosophers[i].is_dead)
                return ;
            i++;
        }
    }
}