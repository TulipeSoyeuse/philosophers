/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:31:36 by romain            #+#    #+#             */
/*   Updated: 2024/02/26 13:22:40 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_done(t_philosopher *philo)
{
	unsigned long	tms;

	tms = philo->params->nb_of_times_must_eat;
	if (tms && tms <= (unsigned long)philo->eat_count)
		return (1);
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

void	routine_death(t_lst *table)
{
	t_philosopher	*philo;
	int				status;

	while (1)
	{
		status = update_sim_status(table);
		if (status)
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
