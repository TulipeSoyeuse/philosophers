/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:41:13 by romain            #+#    #+#             */
/*   Updated: 2024/01/05 18:43:12 by romain           ###   ########.fr       */
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
			&& philo->params->nb_of_times_must_eat <= philo->eat_count)
			return (1);
		cursor = cursor->next;
	}
	philo = cursor->data;
	if (philo->status == is_dead)
		return (1);
	if (philo->params->nb_of_times_must_eat
		&& philo->params->nb_of_times_must_eat <= philo->eat_count)
		return (1);
	return (0);
}

void	ph_dead(t_philosopher *self)
{
	self->status = is_dead;
	printf("%lld %zu died\n", timestamp(), self->rank);
}

void	ph_sleep(t_lst *table)
{
	t_philosopher	*self;

	self = table->data;
	self->status = is_sleeping;
	printf("%lld %zu is sleeping\n", timestamp(), self->rank);
	usleep(self->params->time_to_sleep);
	self->status = is_thinking;
}

void	ph_eat(t_lst *table)
{
	t_philosopher	*self;
	t_philosopher	*right;

	self = table->data;
	right = table->next->data;
	if (take_fork(self, self->rank))
		return ;
	if (take_fork(right, self->rank))
	{
		pthread_mutex_unlock(&(self->left_fork_mutex));
		return ;
	}
	printf("%lld %zu is eating\n", timestamp(), self->rank);
	self->status = is_eating;
	self->last_meal = timestamp();
	usleep(self->params->time_to_eat);
	self->left_fork = available;
	right->left_fork = available;
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
	self->last_meal = timestamp();
	while (!is_sim_must_end(table))
	{
		if (timestamp() - self->last_meal > (long long) self->params->time_to_die)
		{
			ph_dead(self);
			break ;
		}
		if (self->status == is_thinking)
			if (self->left_fork
				&& ((t_philosopher *)table->next->data)->left_fork)
				ph_eat(table);
	}
	return (NULL);
}
