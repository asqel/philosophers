/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:49:22 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/25 21:00:31 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	philo_wait(t_philo *philo, int time)
{
	int64_t	time_end;

	time_end = get_time(philo->ctx) + time;
	while (get_time(philo->ctx) < time_end && !get_is_end(philo->ctx))
		usleep(100);
}

static void	philo_sleep(t_philo *philo)
{
	philo_print(philo, PHILO_ACT_SLEEP);
	philo_wait(philo, philo->ctx->time_to_sleep);
}

static void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat = get_time(philo->ctx);
	pthread_mutex_unlock(&philo->eat_mutex);
}

static void	philo_eat(t_philo *philo, int *eat_count)
{
	philo_print(philo, PHILO_ACT_THINK);
	while (try_take_fork(philo->left_fork))
	{
		if (get_is_end(philo->ctx))
			return ;
		usleep(100);
	}
	philo_print(philo, PHILO_ACT_FORK);
	while (try_take_fork(philo->right_fork))
	{
		if (get_is_end(philo->ctx))
			return (leave_fork(philo->left_fork));
		usleep(100);
	}
	philo_print(philo, PHILO_ACT_FORK);
	set_last_eat(philo);
	philo_print(philo, PHILO_ACT_EAT);
	philo_wait(philo, philo->ctx->time_to_eat);
	leave_fork(philo->left_fork);
	leave_fork(philo->right_fork);
	(*eat_count)++;
}

void	*philo_main(void *arg)
{
	t_philo	*philo;
	int		eat_count;

	eat_count = 0;
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->ctx->start_mutex);
	pthread_mutex_unlock(&philo->ctx->start_mutex);
	while (get_time(philo->ctx) < 0)
		;
	set_last_eat(philo);
	while (1)
	{
		philo_eat(philo, &eat_count);
		philo_sleep(philo);
		if (eat_count == philo->ctx->must_eat)
		{
			pthread_mutex_lock(&philo->ctx->num_eat_mutex);
			philo->ctx->num_eat++;
			pthread_mutex_unlock(&philo->ctx->num_eat_mutex);
		}
		if (get_is_end(philo->ctx))
			return (NULL);
	}
	return (NULL);
}
