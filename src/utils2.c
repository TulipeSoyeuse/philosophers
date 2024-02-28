/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:41:57 by romain            #+#    #+#             */
/*   Updated: 2024/02/28 15:55:41 by rdupeux          ###   ########.fr       */
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

int	eat_enough(t_lst *table)
{
	t_philosopher	*philo;
	int				len;
	int				flag;
	int				i;

	len = get_lst_len(&table);
	i = len;
	flag = 0;
	while (i--)
	{
		philo = table->data;
		if (!philo->params->nb_of_times_must_eat)
			return (0);
		pthread_mutex_lock(&(philo->eat_count_mutex));
		if (philo->eat_count >= philo->params->nb_of_times_must_eat)
			flag++;
		pthread_mutex_unlock(&(philo->eat_count_mutex));
		table = table->next;
	}
	if (flag == len)
		return (1);
	return (0);
}

void	print_eating(t_lst *table)
{
	t_philosopher	*self;

	self = table->data;
	if (!is_sim_must_end(table))
	{
		pthread_mutex_lock(&(self->params->writer));
		printf("%lld %zu is eating\n", timestamp(self->params->start_time),
			self->rank);
		pthread_mutex_unlock(&(self->params->writer));
	}
}

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

int	check(int ac, char **av)
{
	int		i;
	char	*buf;

	i = 1;
	if (*(av[1]) == '0')
		return (1);
	while (i < ac)
	{
		buf = av[i];
		while (*buf)
		{
			if (*buf < '0' || *buf > '9')
				return (1);
			buf++;
		}
		i++;
	}
	return (0);
}
