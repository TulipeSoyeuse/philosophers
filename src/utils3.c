/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:09:07 by rdupeux           #+#    #+#             */
/*   Updated: 2024/02/28 17:12:05 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_think(t_params *params)
{
	if (params->time_to_eat - params->time_to_sleep + 1 > 0
		&& !(params->number_of_philosophers % 2))
		usleep(params->time_to_eat - params->time_to_sleep + 1);
	else if (params->number_of_philosophers % 2)
		usleep(params->time_to_eat + 1);
}
