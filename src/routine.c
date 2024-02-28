/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:41:13 by romain            #+#    #+#             */
/*   Updated: 2024/02/28 16:56:17 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_dead(t_philosopher *self)
{
	self->status = is_dead;
	pthread_mutex_lock(&(self->params->writer));
	printf("%lld %zu died\n", timestamp(self->params->start_time), self->rank);
	pthread_mutex_unlock(&(self->params->writer));
}

void	ph_sleep(t_lst *table)
{
	t_philosopher	*self;

	self = table->data;
	if (!is_sim_must_end(table))
	{
		pthread_mutex_lock(&(self->params->writer));
		printf("%lld %zu is sleeping\n", timestamp(self->params->start_time),
			self->rank);
		pthread_mutex_unlock(&(self->params->writer));
	}
	if (!is_sim_must_end(table))
		usleep(self->params->time_to_sleep);
	if (!is_sim_must_end(table))
	{
		pthread_mutex_lock(&(self->params->writer));
		printf("%lld %zu is thinking\n", timestamp(self->params->start_time),
			self->rank);
		pthread_mutex_unlock(&(self->params->writer));
	}
}

void	ph_eat_pair(t_lst *table)
{
	t_philosopher	*self;
	t_philosopher	*right;

	self = table->data;
	right = table->next->data;
	if (self == right)
		return ;
	take_fork(self, self->rank);
	take_fork(right, self->rank);
	print_eating(table);
	pthread_mutex_lock(&(self->last_meal_mutex));
	self->last_meal = timestamp(0);
	pthread_mutex_unlock(&(self->last_meal_mutex));
	usleep(self->params->time_to_eat);
	pthread_mutex_lock(&(self->eat_count_mutex));
	self->eat_count++;
	pthread_mutex_unlock(&(self->eat_count_mutex));
	pthread_mutex_unlock(&(self->left_fork_mutex));
	pthread_mutex_unlock(&(right->left_fork_mutex));
	ph_sleep(table);
}

void	ph_eat_unpair(t_lst *table)
{
	t_philosopher	*self;
	t_philosopher	*right;

	self = table->data;
	right = table->next->data;
	if (self == right)
		return ;
	take_fork(right, self->rank);
	take_fork(self, self->rank);
	print_eating(table);
	pthread_mutex_lock(&(self->last_meal_mutex));
	self->last_meal = timestamp(0);
	pthread_mutex_unlock(&(self->last_meal_mutex));
	usleep(self->params->time_to_eat);
	pthread_mutex_lock(&(self->eat_count_mutex));
	self->eat_count++;
	pthread_mutex_unlock(&(self->eat_count_mutex));
	pthread_mutex_unlock(&(self->left_fork_mutex));
	pthread_mutex_unlock(&(right->left_fork_mutex));
	ph_sleep(table);
}

void	*routine_main(void *arg)
{
	t_philosopher	*self;
	t_lst			*table;

	table = arg;
	self = table->data;
	while (1)
	{
		pthread_mutex_lock(&(self->last_meal_mutex));
		if (self->last_meal)
		{
			pthread_mutex_unlock(&(self->last_meal_mutex));
			break ;
		}
		pthread_mutex_unlock(&(self->last_meal_mutex));
	}
	while (!is_sim_must_end(table))
	{
		if (self->rank % 2)
			ph_eat_pair(table);
		else
			ph_eat_unpair(table);
		time_to_think(self->params);
	}
	return (NULL);
}
