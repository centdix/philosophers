/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:39:51 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/17 22:04:26 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <errno.h>

# define MAX_PHILO 200
# define EAT 10
# define SLEEP 20
# define THINK 30
# define DEAD 40

typedef enum	e_state
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
	pthread_t		eat_thread;
	pthread_t		dead_thread;
	pthread_t		end_thread;
	t_state			status;
	int				eat_times;
	int				last_eat;
	sem_t			*action_sem;
	struct s_shared	*shared;
}				t_philo;

typedef struct	s_shared
{
	int				nb_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				eat_times;
	sem_t			*write_sem;
	sem_t			*forks_sem;
	sem_t			*done_philo;
	sem_t			*end_sem;
	t_state			glb_status;
}				t_shared;

int				ft_atoi(char *str);

int				init_shared(t_shared *shared, int ac, char **av);
int				init_philo(t_shared *shared);

int				write_err(char *str);
void			write_status(int timestamp, t_philo *philo, int action);

void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
void			ft_think(t_philo *philo);

int				check_status(t_shared *shared);
void			*test_eat(void *arg);
void			*test_dead(void *arg);
void			*test_end(void *arg);

int				get_runtime();

void			*routine(void *arg);

#endif
