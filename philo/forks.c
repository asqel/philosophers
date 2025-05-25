/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 01:08:21 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/25 01:10:04 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->is_taken)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	fork->is_taken = 1;
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

void	leave_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->is_taken = 0;
	pthread_mutex_unlock(&fork->mutex);
}