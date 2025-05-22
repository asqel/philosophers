/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:54:13 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/29 14:54:24 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int philo_is_dead(t_philo *philo)
{
	t_timeval now;
	t_timeval death_time;

	if (philo->is_dead)
		return (1);
	now = philo_get_time(0);
	death_time = time_add(philo->last_eat, philo->ctx->time_to_die);
	if (!philo_time_is_less(now, death_time))
	{
		philo->is_dead = 1;
		philo_print_death(philo);
		return (1);
	}
	return (0);
}

void philo_print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->ctx->mutexes[PH_MUT_PRINTF]);
	pthread_mutex_lock(&philo->ctx->mutexes[PH_MUT_IS_END]);
	if (philo->ctx->is_end == 0)
	{
		philo->ctx->is_end = 1;
		printf("%u %d died\n", get_time_ms(), philo->id);
	}
	pthread_mutex_unlock(&philo->ctx->mutexes[PH_MUT_IS_END]);
	pthread_mutex_unlock(&philo->ctx->mutexes[PH_MUT_PRINTF]);
}