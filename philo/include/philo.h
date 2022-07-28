/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:01:37 by afulmini          #+#    #+#             */
/*   Updated: 2022/01/20 10:58:25 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_data
{
	int				nbr;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				max_meals;
	int				dead;
	int				done;
	pthread_mutex_t	write;
	struct timeval	*start;
}	t_data;

typedef struct s_philo
{
	int					id;
	int					eaten;
	int					last_meal;
	t_fork				*right;
	t_fork				*left;
	t_data				*data;
	pthread_t			tid;
}	t_philo;

typedef struct s_rules
{
	t_fork			**forks;
	t_philo			**philo;
	t_data			*data;
}	t_rules;

int					ft_atoi(const char *nptr);

int					check_arg(char **argv);

int					check_zero(char **av);

int					check_dead(t_philo *philo);

void				print_msg(t_philo *philo, char *str, int mode);

void				*philo_routine(void *philo);

void				my_usleep(int ms);

int					get_timestamp(struct timeval *start);

t_rules				*create_sim(void);

t_rules				*init_rules(int argc, char **argv, t_rules *sim);

t_rules				*free_all(t_rules *sim);

#endif
