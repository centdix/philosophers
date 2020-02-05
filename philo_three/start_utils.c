#include "header.h"

void    wait_eat(int count, t_philosopher *philosophers)
{
    int i;
    int ret;
    int status;

    i = 0;
    while (i < count)
    {
     ret = waitpid(philosophers[i].pid, &status, WNOHANG);
     if (ret == -1)
         break ;
     i++;
    }
}

void    kill_all(int count, t_philosopher *philosophers)
{
    int i;

    i = 0;
    while (i < count)
    {
        kill(philosophers[i].pid, SIGINT);
        i++;
    }
}

void    wait_die(int count, t_philosopher *philosophers)
{
    int i;
    int status;

    while (1)
    {
        i = 0;
        while (i < count)
        {
            if (philosophers[i].is_dead)
            {
                kill_all(count, philosophers);
                waitpid(philosophers[i].pid, &status, WNOHANG);
            }
            i++;
        }
    }
}