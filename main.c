/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:04:49 by romain            #+#    #+#             */
/*   Updated: 2024/01/02 23:32:09 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief start and join all routines ( this function wait for all the thread
/// to finish before returning ), routine himself is defined in routine.c.
/// @param table table where all philosophers are installed
/// @param params rules defining the simulation
void	start_sim(t_lst **table, t_params params)
{
	t_lst	*cursor;

	(void) params;
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
		printf("thread %d exiting\n", ((t_philosopher *) cursor->data)->rank);
		cursor = cursor->next;
	}
	pthread_join(((t_philosopher *)(cursor->data))->thread, NULL);
}

void	init_table(t_lst **table, t_params params)
{
	size_t				i;
	t_philosopher	*philosopher;
	t_lst			*new;

	i = 0;
	while (i++ != params.number_of_philosophers)
	{
		philosopher = malloc(sizeof(t_philosopher));
		philosopher->eat_count = 0;
		philosopher->rank = i;
		new = lst_new(philosopher);
		pthread_mutex_init(&(philosopher->left_fork_mutex), NULL);
		append(table, new);
	}
}

int	main(int ac, char **av)
{
	t_lst		*table;
	t_params	params;

	if (ac - 5 && ac - 6)
		return (1);
	params.number_of_philosophers = ft_atoi(av[1]);
	params.time_to_die = ft_atoi(av[2]);
	params.time_to_eat = ft_atoi(av[3]);
	params.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		params.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		params.number_of_times_each_philosopher_must_eat = 0;
	table = NULL;
	init_table(&table, params);
	start_sim(&table, params);
	pthread_exit(NULL);
}
