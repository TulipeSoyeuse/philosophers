/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:43:09 by romain            #+#    #+#             */
/*   Updated: 2024/02/28 13:23:27 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "../ft_lst/ft_lst.h"
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	is_dead,
	is_alive,
}					t_status;

typedef struct s_params
{
	pthread_mutex_t	writer;
	size_t			number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_of_times_must_eat;
	int				sim_must_end;
	pthread_mutex_t	sim_must_end_mutex;
	long long		start_time;
}					t_params;

typedef struct s_philosopher
{
	size_t			rank;
	size_t			eat_count;
	pthread_mutex_t	eat_count_mutex;
	long long		last_meal;
	pthread_mutex_t	last_meal_mutex;
	t_params		*params;
	t_status		status;
	pthread_mutex_t	left_fork_mutex;
	pthread_t		thread;
}					t_philosopher;

int					ft_atoi(const char *str);
void				*routine_main(void *self);
int					take_fork(t_philosopher *self, size_t id);
long long			timestamp(long long start);
void				ph_dead(t_philosopher *self);
void				routine_death(t_lst *table);
int					eat_enough(t_lst *table);
void				print_eating(t_lst *table);
int					is_sim_must_end(t_lst *table);
#endif
