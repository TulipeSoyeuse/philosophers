/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:43:09 by romain            #+#    #+#             */
/*   Updated: 2024/01/02 22:52:43 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "ft_lst/ft_lst.h"
# include <pthread.h>
#include <stdio.h>

typedef struct s_philosopher
{
	int				rank;
	int				eat_count;

	enum			e_status
	{
		is_eating,
		is_sleeping,
		is_thinking
	};
	enum			e_left_fork
	{
		unavailable,
		available
	};
	pthread_mutex_t	left_fork_mutex;
	pthread_t		thread;
}					t_philosopher;
typedef struct s_params
{
	size_t			number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_times_each_philosopher_must_eat;
}					t_params;

int					ft_atoi(const char *str);
int					routine_main(void *self);
#endif
