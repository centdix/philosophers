#include "header.h"

int     should_take(long time_since_eat, t_philosopher *philosopher)
{
    if (philosopher->eat_times == 0)
        return (1);
    else
    {
        if (time_since_eat > philosopher->param.time_to_eat
        + philosopher->param.time_to_sleep + 5
        || philosopher->param.time_to_die - time_since_eat < 5)
            return (1);
        return (0);
    }
}

void    ft_eat(t_philosopher *philosopher)
{
    long            timestamp;
    long            time_since_eat;

    time_since_eat = get_timediff(philosopher->last_eat);
    timestamp = get_timediff(philosopher->param.start_time);
    if (time_since_eat > philosopher->param.time_to_die)
    {
        philosopher->status = DEAD;
        write_status(timestamp, philosopher->id, DIE);
        return ;
    }
    if (should_take(time_since_eat, philosopher))
        take_forks(philosopher);
    timestamp = get_timediff(philosopher->param.start_time);
    if (philosopher->nb_forks == 2)
    {
        gettimeofday(&philosopher->last_eat, NULL);
        write_status(timestamp, philosopher->id, EAT);
        philosopher->status = EATING;
        philosopher->eat_times++;
        usleep(philosopher->param.time_to_eat * 1000);
        drop_forks(philosopher);
    }
}

void    ft_sleep(t_philosopher *philosopher)
{
    long            timestamp;
    long            time_since_eat;
    long            future_time;

    time_since_eat = get_timediff(philosopher->last_eat);
    timestamp = get_timediff(philosopher->param.start_time);
    if (time_since_eat > philosopher->param.time_to_die)
    {
        philosopher->status = DEAD;
        write_status(timestamp, philosopher->id, DIE);
        return ;
    }
    write_status(timestamp, philosopher->id, SLEEP);
    philosopher->status = SLEEPING;
    future_time = time_since_eat + philosopher->param.time_to_sleep;
    if (future_time > philosopher->param.time_to_die)
    {
        usleep(1000 * (philosopher->param.time_to_die - timestamp));
        timestamp = get_timediff(philosopher->param.start_time);
        write_status(timestamp, philosopher->id, DIE);
        philosopher->status = DEAD;
        return ;
    }
    usleep(philosopher->param.time_to_sleep * 1000);
}

void    ft_think(t_philosopher *philosopher)
{
    long            timestamp;
    long            time_since_eat;

    time_since_eat = get_timediff(philosopher->last_eat);
    timestamp = get_timediff(philosopher->param.start_time);
    if (time_since_eat > philosopher->param.time_to_die)
    {
        philosopher->status = DEAD;
        write_status(timestamp, philosopher->id, DIE);
        return ;
    }
    write_status(timestamp, philosopher->id, THINK);
    philosopher->status = THINKING;
}