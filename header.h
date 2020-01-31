#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_param
{
	int				nb_philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				eat_times;
	struct timeval	start_time;
}				t_param;

typedef struct 	s_philosopher
{
	int			id;
	pthread_t	thread;
	t_param		param;
	int			is_eating;
	int			is_sleeping;
	int			is_thinking;
	int			is_dead;
	int			eat_times;
}				t_philosopher;

int 			write_err(char *str);
int 			ft_atoi(char *str);
t_philosopher	*init_ph(t_param param);
long			get_timediff(struct timeval start, struct timeval now);