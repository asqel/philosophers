/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:35:49 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/29 15:07:20 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void philo_wait(t_philo *philo, int delay_ms)
{
	t_timeval end;

	end = philo_get_time(0);
	end = time_add(end, delay_ms);
	while (philo_time_is_less(philo_get_time(0), end))
	{
		if (philo_is_dead(philo))
			return ;
		usleep(125);
	}
}

void philo_eat_wait(t_philo *philo)
{
	if (philo_is_dead(philo))
		return ;
	philo->last_eat = philo_get_time(0);
	philo_wait(philo, philo->ctx->time_to_eat);
}

void philo_eat(t_philo *philo)
{
	if (philo_is_dead(philo))
		return ;
	philo_print(philo, PHILO_ACT_THINK);
	while (1)
	{
		if (try_take_fork(philo->ctx, philo->left_fork))
			break;
		if (philo_is_dead(philo))
			return ;
		//printf("%d last %d now %dis waiting why\n", philo->id, philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec / 1000, get_time_ms());
	}
	philo_print(philo, PHILO_ACT_FORK);
	while (1)
	{
		if (try_take_fork(philo->ctx, philo->right_fork))
			break;
		if (philo_is_dead(philo))
			return (leave_fork(philo->ctx, philo->left_fork));
	}
	philo_print(philo, PHILO_ACT_FORK);
	philo_print(philo, PHILO_ACT_EAT);
	philo_eat_wait(philo);
	leave_fork(philo->ctx, philo->left_fork);
	leave_fork(philo->ctx, philo->right_fork);
}

void philo_sleep(t_philo *philo)
{
	if (philo_is_dead(philo))
		return ;
	philo_print(philo, PHILO_ACT_SLEEP);
	philo_wait(philo, philo->ctx->time_to_sleep);
}

void *philo_main(void *arg)
{
	t_philo *philo;

	philo =  (t_philo *)arg;
	philo->last_eat = philo_get_time(0);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		if (philo_is_dead(philo))
			break;
		if (get_is_end(philo->ctx))
			break;
	}
	return (NULL);
}
