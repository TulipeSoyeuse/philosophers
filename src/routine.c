/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:41:13 by romain            #+#    #+#             */
/*   Updated: 2024/02/28 13:22:59 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sim_must_end(t_lst *table)
{
	t_philosopher	*philo;
	t_params		*params;
	int				code;

	philo = table->data;
	params = philo->params;
	pthread_mutex_lock(&(params->sim_must_end_mutex));
	code = params->sim_must_end;
	pthread_mutex_unlock(&(params->sim_must_end_mutex));
	return (code);
}

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

void	ph_eat(t_lst *table)
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
	if (self->rank % 2)
		usleep(self->params->time_to_eat / 2);
	while (!is_sim_must_end(table))
	{
		ph_eat(table);
	}
	return (NULL);
}
