/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:43:09 by romain            #+#    #+#             */
/*   Updated: 2024/01/03 18:25:49 by romain           ###   ########.fr       */
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
	is_thinking,
	is_eating,
	is_sleeping
}					t_status;
typedef enum e_left_fork
{
	unavailable,
	available
}					t_left_fork;

typedef struct s_params
{
	size_t			number_of_philosophers;
	int				time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nb_of_times_must_eat;
}					t_params;
typedef struct s_philosopher
{
	size_t			rank;
	size_t			eat_count;
	struct timeval	last_meal;
	t_params		*params;
	t_status		status;
	t_left_fork		left_fork;
	pthread_mutex_t	left_fork_mutex;
	pthread_t		thread;
}					t_philosopher;

int					ft_atoi(const char *str);
void				*routine_main(void *self);
int					take_fork(t_philosopher *self);
#endif
