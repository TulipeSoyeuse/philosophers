/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:41:13 by romain            #+#    #+#             */
/*   Updated: 2024/02/19 11:39:56 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sim_must_end(t_lst *table)
{
	t_philosopher	*philo;
	int				len;

	len = ((t_philosopher *)table->data)->params->number_of_philosophers;
	while (len--)
	{
		philo = table->data;
		if (philo->params->sim_must_end)
			return (1);
		table = table->next;
	}
	return (0);
}

void	ph_dead(t_philosopher *self)
{
	self->status = is_dead;
	printf("%lld %zu died\n", timestamp(self->params->start_time), self->rank);
}

void	ph_sleep(t_lst *table)
{
	t_philosopher	*self;

	if (is_sim_must_end(table))
		return ;
	self = table->data;
	printf("%lld %zu is sleeping\n", timestamp(self->params->start_time),
		self->rank);
	usleep(self->params->time_to_sleep);
	printf("%lld %zu is thinking\n", timestamp(self->params->start_time),
		self->rank);
}

void	ph_eat(t_lst *table)
{
	t_philosopher	*self;
	t_philosopher	*right;

	self = table->data;
	right = table->next->data;
	if (self == right)
		return ;
	pthread_mutex_lock(&self->left_fork_mutex);
	pthread_mutex_lock(&right->left_fork_mutex);
	printf("%lld %zu is eating\n", timestamp(self->params->start_time),
		self->rank);
	self->last_meal = timestamp(0);
	usleep(self->params->time_to_eat);
	pthread_mutex_unlock(&(self->left_fork_mutex));
	pthread_mutex_unlock(&(right->left_fork_mutex));
	self->eat_count++;
	ph_sleep(table);
}

void	*routine_main(void *arg)
{
	t_philosopher	*self;
	t_lst			*table;

	table = arg;
	self = table->data;
	while (!self->last_meal)
		;
	if (self->rank % 2)
		usleep(self->params->time_to_eat / 2);
	while (!is_sim_must_end(table))
	{
		ph_eat(table);
	}
	return (NULL);
}
