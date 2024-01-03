/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:17:08 by romain            #+#    #+#             */
/*   Updated: 2024/01/03 18:30:09 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r'
		|| c == '\f')
		return (1);
	else
		return (0);
}

static int	get_signe(const char c)
{
	if (c == '-')
		return (-1);
	if (c == '+' || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	res = 0;
	while (ft_isspace(str[0]))
		str++;
	signe = get_signe(str[0]);
	if (!ft_isdigit(*str))
		str++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * signe);
}

int	take_fork(t_philosopher *self)
{
	struct timeval	time;

	if (self->left_fork == unavailable)
		return (1);
	pthread_mutex_lock(&(self->left_fork_mutex));
	self->left_fork = unavailable;
	gettimeofday(&time, NULL);
	printf("%d %zu as taken a fork\n", time.tv_usec, self->rank);
	return (0);
}
