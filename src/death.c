/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:31:36 by romain            #+#    #+#             */
/*   Updated: 2024/02/28 11:02:22 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_done(t_philosopher *philo)
{
	unsigned long	last_meal;

	pthread_mutex_lock(&(philo->last_meal_mutex));
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&(philo->last_meal_mutex));
	if (!((long long)philo->params->time_to_die + last_meal - timestamp(0))
		&& last_meal)
	{
		ph_dead(philo);
		return (1);
	}
	return (0);
}

int	update_sim_status(t_lst *table)
{
	t_lst			*cursor;
	t_philosopher	*philo;

	cursor = table;
	while (cursor->next != table)
	{
		philo = cursor->data;
		if (sim_done(philo))
			return (1);
		cursor = cursor->next;
	}
	philo = cursor->data;
	if (sim_done(philo))
		return (1);
	return (0);
}

void	routine_death(t_lst *table)
{
	t_philosopher	*philo;
	int				status;
	int				cnt;

	cnt = 0;
	while (1)
	{
		cnt++;
		status = update_sim_status(table);
		if (status || (!(cnt % 10) && eat_enough(table)))
		{
			philo = table->data;
			pthread_mutex_lock(&(philo->params->sim_must_end_mutex));
			philo->params->sim_must_end = 1;
			pthread_mutex_unlock(&(philo->params->sim_must_end_mutex));
			return ;
		}
	}
	return ;
}
