/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:41:13 by romain            #+#    #+#             */
/*   Updated: 2024/01/03 18:30:12 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sim_must_end(t_lst *table)
{
	t_lst			*cursor;
	t_philosopher	*philo;

	cursor = table;
	while (cursor->next != table)
	{
		philo = cursor->data;
		if (philo->status == is_dead)
			return (1);
		if (philo->params->nb_of_times_must_eat
			&& philo->params->nb_of_times_must_eat == philo->eat_count)
			return (1);
		cursor = cursor->next;
	}
	philo = cursor->data;
	if (philo->status == is_dead)
		return (1);
	return (0);
}

void	ph_dead(t_philosopher *self, struct timeval time)
{
	self->status = is_dead;
	printf("%d %zu died\n", time.tv_usec, self->rank);
}

void	ph_sleep(t_lst *table)
{
	t_philosopher	*self;
	struct timeval	time;

	self = table->data;
	self->status = is_sleeping;
	gettimeofday(&time, NULL);
	printf("%d %zu is sleeping\n", time.tv_usec, self->rank);
	usleep(self->params->time_to_sleep);
	self->status = is_thinking;
}

void	ph_eat(t_lst *table, struct timeval time)
{
	t_philosopher	*self;
	t_philosopher	*right;

	self = table->data;
	right = table->next->data;
	if (take_fork(self))
		return ;
	if (take_fork(right))
	{
		pthread_mutex_unlock(&(self->left_fork_mutex));
		return ;
	}
	printf("%d %zu is eating\n", time.tv_usec, self->rank);
	gettimeofday(&time, NULL);
	self->status = is_eating;
	self->last_meal = time;
	usleep(self->params->time_to_eat);
	self->left_fork = available;
	right->left_fork = available;
	pthread_mutex_unlock(&(self->left_fork_mutex));
	pthread_mutex_unlock(&(right->left_fork_mutex));
	ph_sleep(table);
}

void	*routine_main(void *arg)
{
	t_philosopher	*self;
	t_lst			*table;
	struct timeval	time;

	table = arg;
	self = table->data;
	gettimeofday(&time, NULL);
	self->last_meal = time;
	while (!is_sim_must_end(table))
	{
		gettimeofday(&time, NULL);
		if (time.tv_usec - self->last_meal.tv_usec > self->params->time_to_die)
		{
			ph_dead(self, time);
			break ;
		}
		if (self->status == is_thinking)
			if (self->left_fork
				&& ((t_philosopher *)table->next->data)->left_fork)
				ph_eat(table, time);
		if (self->params->nb_of_times_must_eat
			&& self->params->nb_of_times_must_eat == self->eat_count)
			break ;
	}
	return (NULL);
}
