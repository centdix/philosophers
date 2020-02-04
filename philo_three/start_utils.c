#include "header.h"

void    wait_eat(int count, t_philosopher *philosophers)
{
    int i;

    i = 0;
    while (i < count)
    {
        waitpid(philosophers[i].pid, NULL, 0);
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