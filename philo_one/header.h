/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:39:51 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/14 22:27:45 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define MAX_PHILO 200
# define EAT 10
# define SLEEP 20
# define THINK 30
# define DEAD 40

int					g_forks[MAX_PHILO];
pthread_mutex_t		*g_mutex;
pthread_mutex_t		g_write_mutex;

typedef enum  	e_state
{
	running,
	eating,
	sleeping,
	thinking,
	dead,
	end
}				t_state;

typedef struct	s_philo
{
	int				id;
	pthread_t		thread;
	t_state			status;
	int				eat_times;
	int				last_eat;
	struct s_shared	*shared;
}				t_philo;

typedef struct	s_shared
{
	int				nb_philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				eat_times;
	t_state			glb_status;
	t_philo			philo_lst[MAX_PHILO];
}				t_shared;

int				ft_atoi(char *str);
int				ft_min(int a, int b);
int				ft_max(int a, int b);

int				init_shared(t_shared *shared, int ac, char **av);
int				init_philo(t_shared *shared);
void			init_forks(int count);
int				init_mutex(int count);

int				write_err(char *str);
void			write_status(int timestamp, int id, int action);

void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
void			ft_think(t_philo *philo);

int				check_dead(t_shared *shared);
int				check_eat(t_shared *shared);

int				get_runtime();

void			*routine(void *arg);

#endif
