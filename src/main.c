/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:04:49 by romain            #+#    #+#             */
/*   Updated: 2024/02/28 15:54:13 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch(t_lst **table)
{
	size_t			len;
	t_lst			*cursor;
	t_philosopher	*philo;
	long long		time;

	len = get_lst_len(table);
	cursor = *table;
	time = timestamp(0);
	while (len--)
	{
		philo = cursor->data;
		pthread_mutex_lock(&(philo->last_meal_mutex));
		philo->last_meal = time;
		pthread_mutex_unlock(&(philo->last_meal_mutex));
		cursor = cursor->next;
	}
}

/// @brief start and join all routines ( this function wait for all the thread
/// to finish before returning ), routine himself is defined in routine.c.
/// @param table table where all philosophers are installed
/// @param params rules defining the simulation
void	start_sim(t_lst **table)
{
	t_lst	*cursor;

	cursor = *table;
	((t_philosopher *)(cursor->data))->params->start_time = timestamp(0);
	while (cursor->next != *table)
	{
		pthread_create(&((t_philosopher *)(cursor->data))->thread, NULL,
			&routine_main, cursor);
		cursor = cursor->next;
	}
	pthread_create(&((t_philosopher *)(cursor->data))->thread, NULL,
		&routine_main, cursor);
	launch(table);
	cursor = *table;
	routine_death(cursor);
	while (cursor->next != *table)
	{
		pthread_join(((t_philosopher *)(cursor->data))->thread, NULL);
		cursor = cursor->next;
	}
	pthread_join(((t_philosopher *)(cursor->data))->thread, NULL);
}

int	init_table(t_lst **table, t_params *params)
{
	size_t			i;
	t_philosopher	*philosopher;
	t_lst			*new;

	i = 0;
	while (i++ != params->number_of_philosophers)
	{
		philosopher = malloc(sizeof(t_philosopher));
		if (!philosopher)
			return (1);
		philosopher->eat_count = 0;
		philosopher->rank = i;
		philosopher->params = params;
		philosopher->last_meal = 0;
		new = lst_new(philosopher);
		if (!new)
			return (1);
		pthread_mutex_init(&(philosopher->left_fork_mutex), NULL);
		pthread_mutex_init(&(philosopher->last_meal_mutex), NULL);
		if (params->nb_of_times_must_eat)
			pthread_mutex_init(&(philosopher->eat_count_mutex), NULL);
		append(table, new);
	}
	return (0);
}

void	ph_cleanup(void *data)
{
	t_philosopher	*ph;

	ph = data;
	pthread_mutex_destroy(&(ph->left_fork_mutex));
	pthread_mutex_destroy(&(ph->last_meal_mutex));
	if (ph->params->nb_of_times_must_eat)
		pthread_mutex_destroy(&(ph->eat_count_mutex));
	free(ph);
}

int	main(int ac, char **av)
{
	t_lst		*table;
	t_params	params;

	if ((ac - 5 && ac - 6) || check(ac, av))
		return (1);
	params.number_of_philosophers = ft_atoi(av[1]);
	params.time_to_die = ft_atoi(av[2]);
	params.time_to_eat = ft_atoi(av[3]) * 1000;
	params.time_to_sleep = ft_atoi(av[4]) * 1000;
	params.sim_must_end = 0;
	params.start_time = 0;
	pthread_mutex_init(&(params.writer), NULL);
	pthread_mutex_init(&(params.sim_must_end_mutex), NULL);
	if (ac == 6)
		params.nb_of_times_must_eat = ft_atoi(av[5]);
	else
		params.nb_of_times_must_eat = 0;
	table = NULL;
	if (!init_table(&table, &params))
		start_sim(&table);
	free_lst(table, &ph_cleanup);
	pthread_mutex_destroy(&(params.sim_must_end_mutex));
	pthread_mutex_destroy(&(params.writer));
}
