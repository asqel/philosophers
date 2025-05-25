/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 01:58:56 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/25 01:41:56 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static void	init_forks(t_context *ctx)
{
	int	i;

	ctx->forks = malloc(ctx->philo_num * sizeof(t_fork));
	i = 0;
	while (i < ctx->philo_num)
	{
		pthread_mutex_init(&ctx->forks[i].mutex, NULL);
		ctx->forks[i].is_taken = 0;
		i++;
	}
}

static void	init_mutexes(t_context *ctx)
{
	pthread_mutex_init(&ctx->num_eat_mutex, NULL);
	pthread_mutex_init(&ctx->is_end_mutex, NULL);
	pthread_mutex_init(&ctx->printf_mutex, NULL);
}

static void	init_philos(t_context *ctx)
{
	int	i;

	ctx->philos = malloc(ctx->philo_num * sizeof(t_philo));
	i = -1;
	while (++i < ctx->philo_num)
	{
		ctx->philos[i].id = i + 1;
		ctx->philos[i].ctx = ctx;
		pthread_mutex_init(&ctx->philos[i].eat_mutex, NULL);
		ctx->philos[i].last_eat = get_time(ctx);
		if (i % 2 == 0)
		{
			ctx->philos[i].left_fork = &ctx->forks[i];
			ctx->philos[i].right_fork = &ctx->forks[(i + 1) % ctx->philo_num];
		}
		else
		{
			ctx->philos[i].left_fork = &ctx->forks[(i + 1) % ctx->philo_num];
			ctx->philos[i].right_fork = &ctx->forks[i];
		}
	}
}

static void	init_threads(t_context *ctx)
{
	int	i;

	ctx->threads = malloc((ctx->philo_num + 1) * sizeof(pthread_t));
	pthread_create(&ctx->threads[ctx->philo_num], NULL, mother_main, ctx);
	i = 0;
	while (i < ctx->philo_num)
	{
		pthread_create(&ctx->threads[i], NULL, philo_main, &ctx->philos[i]);
		i++;
	}
	ctx->start_time = get_time(ctx) + 1000;
	pthread_mutex_unlock(&ctx->start_mutex);
}

int	init_ctx(t_context *ctx, int argc, char **argv)
{
	memset(ctx, 0, sizeof(t_context));
	ctx->must_eat = -1;
	if (argc != 5 && argc != 6)
		return (write(1, "Error: Wrong number of arguments\n", 26), 1);
	if (ft_atoi(argv[1], &ctx->philo_num) || (ctx->philo_num <= 0))
		return (write_error("Error: arg 1 must be a positive integer"), 1);
	if (ft_atoi(argv[2], &ctx->time_to_die) || (ctx->time_to_die <= 0))
		return (write_error("Error: arg 2 must be a positive integer"), 1);
	if (ft_atoi(argv[3], &ctx->time_to_eat) || (ctx->time_to_eat <= 0))
		return (write_error("Error: arg 3 must be a positive integer"), 1);
	if (ft_atoi(argv[4], &ctx->time_to_sleep) || (ctx->time_to_sleep <= 0))
		return (write_error("Error: arg 4 must be a positive integer"), 1);
	if (argc == 6)
		if (ft_atoi(argv[5], &ctx->must_eat) || (ctx->must_eat <= 0))
			return (write_error("Error: arg 5 must be a positive integer"), 1);
	init_forks(ctx);
	init_mutexes(ctx);
	init_philos(ctx);
	pthread_mutex_init(&ctx->start_mutex, NULL);
	pthread_mutex_lock(&ctx->start_mutex);
	init_threads(ctx);
	return (0);
}
