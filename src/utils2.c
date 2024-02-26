/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:41:57 by romain            #+#    #+#             */
/*   Updated: 2024/02/19 11:26:13 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(long long start)
{
	struct timeval	t;

	if (!start)
	{
		gettimeofday(&t, NULL);
		return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	}
	else
	{
		gettimeofday(&t, NULL);
		return ((t.tv_sec * 1000) + (t.tv_usec / 1000) - start);
	}
}
