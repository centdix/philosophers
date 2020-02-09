#include "header.h"

void    routine_with_option(t_philosopher *philosopher)
{
    while (philosopher->eat_times < philosopher->param.eat_times)
    {
        ft_eat(philosopher);
        if (philosopher->status != DEAD)
            ft_sleep(philosopher);
        if (philosopher->status != DEAD)
            ft_think(philosopher);
    }
}

void    *routine(void *arg)
{
    t_philosopher *philosopher;

    philosopher = (t_philosopher *)arg;
    if (philosopher->param.eat_times == -1)
    {
        while (philosopher->status != DEAD)
        {
            ft_eat(philosopher);
            if (philosopher->status != DEAD)
                ft_sleep(philosopher);
            if (philosopher->status != DEAD)
                ft_think(philosopher);
        }
    }
    else
        routine_with_option(philosopher);
    return (NULL);
}

int     start(t_param param)
{
    t_philosopher   *philosophers;
    int             i;

    init_philosophers(&philosophers, param);
    init_mutex(&g_mutex, param.nb_philosophers);
    init_forks(&g_forks, param.nb_philosophers);
    i = 0;
    while (i < param.nb_philosophers)
    {
        pthread_create(&philosophers[i].thread, NULL, routine, &philosophers[i]);
        i++;
    }
    if (param.eat_times == -1)
        wait_die(philosophers, param.nb_philosophers);
    else
        wait_eat(philosophers, param.nb_philosophers);
    return (0);
}

int     main(int ac, char **av)
{
    t_param     param;

    if (ac < 5 || ac > 6)
        return (write_err("error: argument\n"));
    param.nb_philosophers = ft_atoi(av[1]);
    if (param.nb_philosophers < 1)
        return (write_err("error: argument\n"));
    param.time_to_die = ft_atoi(av[2]);
    param.time_to_eat = ft_atoi(av[3]);
    param.time_to_sleep = ft_atoi(av[4]);
    if (ac == 5)
        param.eat_times = -1;
    else
    {
        param.eat_times = ft_atoi(av[5]);
        if (param.eat_times <= 0)
            return (write_err("error: argument\n"));
    }
    gettimeofday(&param.start_time, NULL);
    return (start(param));
}