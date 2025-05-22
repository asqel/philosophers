/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:34:11 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/29 15:31:49 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

int	init_forks(t_context *ctx) {
	int	i;

	ctx->forks = malloc(sizeof(t_fork) * ctx->philo_len);
	if (!ctx->forks)
		return (1);
	i = -1;
	while (++i < ctx->philo_len)
	{
		ctx->forks[i].is_taken = 0;
		pthread_mutex_init(&ctx->forks[i].mutex, NULL);
	}
	return (0);
}

int	init_mutexes(t_context *ctx) {
	int	i;

	i = -1;
	while (++i < MAX_MUTEX)
		pthread_mutex_init(&ctx->mutexes[i], NULL);
	return (0);
}

int	init_philos(t_context *ctx) {
	int	i;

	ctx->philos = malloc(sizeof(t_philo) * ctx->philo_len);
	ctx->threads = malloc(sizeof(pthread_t) * ctx->philo_len);
	if (!ctx->philos)
		return (1);
	i = -1;
	while (++i < ctx->philo_len)
	{
		ctx->philos[i].id = i;
		ctx->philos[i].is_dead = 0;
		ctx->philos[i].ctx = ctx;
		ctx->philos[i].left_fork = i;
		ctx->philos[i].right_fork = (i + 1) % ctx->philo_len;
		if (i % 2 != 0)
		{
			ctx->philos[i].left_fork = (i + 1) % ctx->philo_len;
			ctx->philos[i].right_fork = i;
		}
	}
	return (0);
}

void init_threads(t_context *ctx) {
	int	i;

	philo_get_time(1);
	i = -1;
	while (++i < ctx->philo_len)
		pthread_create(&ctx->threads[i], NULL, philo_main, &ctx->philos[i]);
	i = -1;
	while (++i < ctx->philo_len)
		pthread_join(ctx->threads[i], NULL);
}

int init_ctx(t_context *ctx, int argc, char **argv)
{
	memset(ctx, 0, sizeof(t_context));
	if (argc != 5 && argc != 6)
		return (write_error_usage(argv[0]), 1);
	if (ft_atoi(argv[1], &ctx->philo_len) || (ctx->philo_len <= 0))
		return (write_error("Error\narg 1 must be a positive integer"), 1);
	if (ft_atoi(argv[2], &ctx->time_to_die) || (ctx->time_to_die <= 0))
		return (write_error("Error\narg 2 must be a positive integer"), 1);
	if (ft_atoi(argv[3], &ctx->time_to_eat) || (ctx->time_to_eat <= 0))
		return (write_error("Error\narg 3 must be a positive integer"), 1);
	if (ft_atoi(argv[4], &ctx->time_to_sleep) || (ctx->time_to_sleep <= 0))
		return (write_error("Error\narg 4 must be a positive integer"), 1);
	if (argc == 6)
		if (ft_atoi(argv[5], &ctx->num_eat) || (ctx->num_eat <= 0))
			return (write_error("Error\narg 5 must be a positive integer"), 1);
	if (init_forks(ctx))
		return (write_error("Error\ninit forks"), 1);
	if (init_mutexes(ctx))
		return (write_error("Error\ninit mutexes"), 1);
	if (init_philos(ctx))
		return (write_error("Error\ninit philos"), 1);
	init_threads(ctx);
	return (0);
}

void exit_ctx(t_context *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philo_len)
		pthread_mutex_destroy(&ctx->forks[i].mutex);
	free(ctx->forks);
	free(ctx->threads);
	free(ctx->philos);
	i = -1;
	while (++i < MAX_MUTEX)
		pthread_mutex_destroy(&ctx->mutexes[i]);
}