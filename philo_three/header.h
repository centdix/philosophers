/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:38:59 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/05 19:04:34 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

# define TAKE 0
# define DROP 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

int		g_nb_forks;
sem_t	*g_semaphore;

typedef struct	s_param
{
	int				nb_philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				eat_times;
	struct timeval	start_time;
}				t_param;

typedef struct	s_philosopher
{
	int				id;
	pid_t			pid;
	t_param			param;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	int				is_dead;
	int				eat_times;
	struct timeval	last_eat;
}				t_philosopher;

int				ft_strlen(char *str);
int				ft_atoi(char *str);
char			*ft_strdup(char *str);
char			*ft_strjoin(char *str1, char *str2);
char			*ft_itoa(int n);
t_philosopher	*init_ph(t_param param);
long			get_timediff(struct timeval start, struct timeval now);

int				write_err(char *str);
void			write_status(long timestamp, int id, int action);

void			ft_eat(t_philosopher *philosopher, long *timestamp);
void			ft_sleep(t_philosopher *philosopher, long *timestamp);
void			ft_think(t_philosopher *philosopher, long *timestamp);
void			keep_trying(t_philosopher *philosopher, long *timestamp);

void			wait_eat(int count, t_philosopher *philosophers);
void			wait_die(int count, t_philosopher *philosophers);

#endif
