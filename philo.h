/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:43:09 by romain            #+#    #+#             */
/*   Updated: 2024/01/02 21:14:44 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "ft_lst/ft_lst.h"
# include "libft/libft.h"
# include <pthread.h>

typedef struct s_philosopher
{
	int				rank;
	int				eat_count;

	enum			e_status
	{
		is_eating,
		is_sleeping,
		is_thinking,
	};

	pthread_mutex_t	left_fork;
	pthread_t		thread;
}					t_philosopher;
#endif
