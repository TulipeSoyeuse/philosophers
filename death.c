/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:31:36 by romain            #+#    #+#             */
/*   Updated: 2024/02/19 11:36:00 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_done(t_philosopher *philo)
{
	if (philo->params->nb_of_times_must_eat
		&& philo->params->nb_of_times_must_eat <= (unsigned long)philo->eat_count)
	{
		printf("number of eating reach by %zu", philo->rank);
		return (1);
	}
	if (!((long long)philo->params->time_to_die + philo->last_meal
			- timestamp(0)) && philo->last_meal)
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

void	*routine_death(t_lst *table)
{
	while (1)
		if (update_sim_status(table))
		{
			((t_philosopher *)table->data)->params->sim_must_end = 1;
			return (NULL);
		}
	return (NULL);
}
