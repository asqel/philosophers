/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:28:41 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/05 01:22:06 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_philo *philo)
{
	uint32_t	now;

	pthread_mutex_lock(&philo->context->is_end_mutex);
	if (philo->is_dead == 1 || philo->context->is_end == 1) {
		philo->context->is_end = 1;
		pthread_mutex_unlock(&philo->context->is_end_mutex);
		return (1);
	}
	now = get_time_ms(0);
	if (now > philo->last_eat + philo->context->time_to_die)
	{
		philo->is_dead = 1;
		philo->context->is_end = 1;
		pthread_mutex_unlock(&philo->context->is_end_mutex);
		pthread_mutex_lock(&philo->context->who_died_mutex);
		if (philo->context->who_died == -1)
			philo->context->who_died = philo->id;
		pthread_mutex_unlock(&philo->context->who_died_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->context->is_end_mutex);
	return (0);
}
