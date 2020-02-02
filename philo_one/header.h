#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define TAKE 0
#define DROP 1
#define EAT 2
#define SLEEP 3
#define THINK 4
#define DIE 5

int 				*g_forks;
pthread_mutex_t		g_mutex;

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
	int				id;
	pthread_t		thread;
	t_param			param;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	int				is_dead;
	int				eat_times;
	struct timeval 	last_eat;
}				t_philosopher;

int 			write_err(char *str);
int 			ft_atoi(char *str);
t_philosopher	*init_ph(t_param param);
long			get_timediff(struct timeval start, struct timeval now);
void			write_status(long timestamp, int id, int action);

int    			*init_forks(t_param param);
int     		check_forks(int *forks, t_philosopher *philosopher);
void    		take_drop_forks(int *forks, t_philosopher *philosopher, int action);

void			ft_eat(t_philosopher *philosopher);
void			ft_sleep(t_philosopher *philosopher);
void			ft_think(t_philosopher *philosopher);
void			keep_trying(t_philosopher *philosopher);

void    		wait_eat(int count, t_philosopher *philosophers);
void			wait_die(int count, t_philosopher *philosophers);
