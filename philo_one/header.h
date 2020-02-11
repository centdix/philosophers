/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:39:51 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:39:53 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define TAKE 0
# define DROP 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5
# define EATING 6
# define SLEEPING 7
# define THINKING 8
# define DEAD 9

int					*g_forks;
pthread_mutex_t		*g_mutex;

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
	pthread_t		thread;
	t_param			param;
	int				status;
	int				has_left;
	int				has_right;
	int				eat_times;
	struct timeval	last_eat;
}				t_philosopher;

int				ft_atoi(char *str);
int				ft_min(int a, int b);
int				ft_max(int a, int b);
long			get_timediff(struct timeval start);

int				ft_strlen(char *str);
char			*ft_strdup(char *str);
char			*ft_strjoin(char *str1, char *str2);
char			*ft_itoa(int n);

int				init_philosophers(t_philosopher **philosophers, t_param param);
int				init_mutex(pthread_mutex_t **g_mutex, int count);
int				init_forks(int **g_forks, int count);

int				write_err(char *str);
void			write_status(long timestamp, int id, int action);

void			take_forks(t_philosopher *philosopher);
void			drop_forks(t_philosopher *philosopher);

void			ft_eat(t_philosopher *philosopher);
void			ft_sleep(t_philosopher *philosopher);
void			ft_think(t_philosopher *philosopher);

void			wait_eat(t_philosopher *philosophers, int count);
void			wait_die(t_philosopher *philosophers, int count);

#endif
