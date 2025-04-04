/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:28:39 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/05 01:47:29 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

void init_philos(t_context *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		ctx->philos[i].context = ctx;
		ctx->philos[i].id = i;
		ctx->philos[i].is_dead = 0;
		ctx->philos[i].last_eat = 0;
		ctx->philos[i].action = -1;
		ctx->philos[i].left = i;
		ctx->philos[i].right = (i + 1) % ctx->philo_count;
		if (i % 2 == 0)
		{
			ctx->philos[i].left = (i + 1) % ctx->philo_count;
			ctx->philos[i].right = i;
		}
		pthread_mutex_init(&ctx->philos[i].has_started, NULL);
		pthread_mutex_lock(&ctx->philos[i].has_started);
		pthread_mutex_init(&ctx->philos[i].action_mutex, NULL);
		pthread_create(&ctx->philos[i].thread, NULL, philo_main, &ctx->philos[i]);
		i++;
	}
}

int	init_ctx(t_context *ctx)
{
	int	i;
	ctx->philos = malloc(sizeof(t_philo) * ctx->philo_count);
	if (ctx->philos == NULL)
		return (1);
	ctx->forks = malloc(sizeof(t_fork) * ctx->philo_count);
	if (ctx->forks == NULL)
		return (free(ctx->philos), 1);
	i = -1;
	memset(ctx->forks, 0, sizeof(t_fork) * ctx->philo_count);
	while (++i < ctx->philo_count)
		pthread_mutex_init(&ctx->forks[i].mutex, NULL);
	ctx->is_end = 0;
	pthread_mutex_init(&ctx->is_end_mutex, NULL);
	pthread_mutex_init(&ctx->who_died_mutex, NULL);
	init_philos(ctx);
	pthread_create(&ctx->mother_thread, NULL, mother_main, ctx);
	return (0);
}