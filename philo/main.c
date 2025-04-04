/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:21:06 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/05 01:49:37 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "string.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void philo_wait(t_philo *philo, int time)
{
	uint32_t	start;

	start = get_time_ms(0);
	while (get_time_ms(0) < start + time)
		if (philo_is_dead(philo))
			return ;
}

int philo_eat(t_philo *philo)
{
	if (philo_is_dead(philo))
		return (1);
	if (take_forks(philo) != 0)
		return (1);
	philo->last_eat = get_time_ms(0);
	if (philo_is_dead(philo))
		return (leave_fork(philo, philo->left), leave_fork(philo, philo->right), 1);
	philo_set_action(philo, PHILO_ACT_EAT);
	philo_wait(philo, philo->context->time_to_eat);
	leave_fork(philo, philo->left);
	leave_fork(philo, philo->right);
	return (philo_is_dead(philo));
}

int philo_sleep(t_philo *philo)
{
	uint32_t	start;

	philo_set_action(philo, PHILO_ACT_SLEEP);
	philo_wait(philo, philo->context->time_to_sleep);
	return (philo_is_dead(philo));
}

void *philo_main(void *arg)
{
	t_philo		*philo = ((t_philo *)arg);

	pthread_mutex_lock(&philo->has_started);
	while (!get_is_end(philo->context))
	{
		if (philo_eat(philo))
			break;
		if (philo_sleep(philo))
			break;
		if (philo_is_dead(philo))
			break;
	}
	pthread_mutex_unlock(&philo->has_started);
	return (NULL);
}

void *mother_main(void *arg)
{
	t_context	*ctx;
	int			i;

	ctx = (t_context *)arg;
	while (!get_is_end(ctx))
	{
		i = -1;
		while (++i < ctx->philo_count)
		{
			if (get_philo_action(&ctx->philos[i]) != -1)
				philo_print(&ctx->philos[i]);
		}
	}
	pthread_mutex_lock(&ctx->who_died_mutex);
	if (ctx->who_died != -1)
		printf("%u %d died\n", get_time_ms(0), ctx->who_died + 1);
	pthread_mutex_unlock(&ctx->who_died_mutex);
	return (NULL);
}

int	main(argc, argv)
{
	t_context	context;
	int			i;

	context.time_to_die = 800;
	context.time_to_eat = 200;
	context.time_to_sleep = 200;
	context.philo_count = 5;
	if (init_ctx(&context))
		return (write_error("Error: malloc failed\n"));
	get_time_ms(1);
	i = -1;
	while (++i < context.philo_count)
		pthread_mutex_unlock(&context.philos[i].has_started);

	pthread_join(context.mother_thread, NULL);
	i = -1;
	while (++i < context.philo_count)
		pthread_join(context.philos[i].thread, NULL);
	i = -1;
	while (++i < context.philo_count)
	{
		pthread_mutex_destroy(&context.philos[i].action_mutex);
		pthread_mutex_destroy(&context.philos[i].has_started);
		pthread_mutex_destroy(&context.forks[i].mutex);
	}
	free(context.philos);
	free(context.forks);
	pthread_mutex_destroy(&context.is_end_mutex);
	pthread_mutex_destroy(&context.who_died_mutex);
	return (0);
}
