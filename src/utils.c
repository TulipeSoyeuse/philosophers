/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:17:08 by romain            #+#    #+#             */
/*   Updated: 2024/02/28 13:21:47 by rdupeux          ###   ########.fr       */
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

int	take_fork(t_philosopher *self, size_t id)
{
	pthread_mutex_lock(&(self->left_fork_mutex));
	pthread_mutex_lock(&(self->params->writer));
	printf("%lld %zu as taken a fork from %zu\n",
		timestamp(self->params->start_time), id, self->rank);
	pthread_mutex_unlock(&(self->params->writer));
	return (0);
}
