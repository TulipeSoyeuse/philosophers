/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:43:09 by romain            #+#    #+#             */
/*   Updated: 2024/01/31 18:00:19 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "ft_lst/ft_lst.h"
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	is_dead,
	is_alive,
}					t_status;
typedef enum e_left_fork
{
	unavailable,
	available
}					t_left_fork;

typedef struct s_params
{
	size_t			number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_of_times_must_eat;
	int				sim_must_end;
}					t_params;

typedef struct s_philosopher
{
	size_t			rank;
	size_t			eat_count;
	long long		last_meal;
	t_params		*params;
	t_status		status;
	t_left_fork		left_fork;
	pthread_mutex_t	left_fork_mutex;
	pthread_t		thread;
}					t_philosopher;

int					ft_atoi(const char *str);
void				*routine_main(void *self);
int					take_fork(t_philosopher *self, size_t id);
long long			timestamp(void);
void				ph_dead(t_philosopher *self);
void				*routine_death(void *arg);
#endif
