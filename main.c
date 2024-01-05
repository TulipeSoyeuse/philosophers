/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:04:49 by romain            #+#    #+#             */
/*   Updated: 2024/01/05 19:03:28 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief start and join all routines ( this function wait for all the thread
/// to finish before returning ), routine himself is defined in routine.c.
/// @param table table where all philosophers are installed
/// @param params rules defining the simulation
void	start_sim(t_lst **table)
{
	t_lst	*cursor;

	printf("sim starting at %lld\n", timestamp());
	cursor = *table;
	while (cursor->next != *table)
	{
		pthread_create(&((t_philosopher *)(cursor->data))->thread, NULL,
			&routine_main, cursor);
		cursor = cursor->next;
	}
	pthread_create(&((t_philosopher *)(cursor->data))->thread, NULL,
		&routine_main, cursor);
	cursor = (*table);
	while (cursor->next != *table)
	{
		pthread_join(((t_philosopher *)(cursor->data))->thread, NULL);
		printf("thread %zu exiting\n", ((t_philosopher *)cursor->data)->rank);
		cursor = cursor->next;
	}
	pthread_join(((t_philosopher *)(cursor->data))->thread, NULL);
	printf("thread %zu exiting\n", ((t_philosopher *)cursor->data)->rank);
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
		philosopher->status = is_thinking;
		philosopher->left_fork = available;
		philosopher->params = params;
		new = lst_new(philosopher);
		if (!new)
			return (1);
		pthread_mutex_init(&(philosopher->left_fork_mutex), NULL);
		append(table, new);
	}
	return (0);
}
void ph_cleanup(void *data)
{
	t_philosopher *ph;

	ph = data;
	pthread_mutex_destroy(&(ph->left_fork_mutex));
	free(ph);
}

int	main(int ac, char **av)
{
	t_lst		*table;
	t_params	params;

	if (ac - 5 && ac - 6)
		return (1);
	params.number_of_philosophers = ft_atoi(av[1]);
	params.time_to_die = ft_atoi(av[2])* 1000;
	params.time_to_eat = ft_atoi(av[3])* 1000;
	params.time_to_sleep = ft_atoi(av[4])* 1000;
	if (ac == 6)
		params.nb_of_times_must_eat = ft_atoi(av[5]);
	else
		params.nb_of_times_must_eat = 0;
	table = NULL;
	if (init_table(&table, &params))
		return (1);
	start_sim(&table);
	free_lst(table, &ph_cleanup);
}
