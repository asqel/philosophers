/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mother.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:49:27 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/25 03:24:18 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	print_death(t_context *ctx, int i)
{
	pthread_mutex_unlock(&ctx->philos[i].eat_mutex);
	pthread_mutex_lock(&ctx->is_end_mutex);
	ctx->is_end = 1;
	pthread_mutex_unlock(&ctx->is_end_mutex);
	pthread_mutex_lock(&ctx->printf_mutex);
	printf("%d %d %s\n", (int)get_time(ctx), i + 1, "died");
	pthread_mutex_unlock(&ctx->printf_mutex);
}

int	check_eat(t_context *ctx)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&ctx->num_eat_mutex);
	if (ctx->num_eat == ctx->philo_num)
	{
		pthread_mutex_lock(&ctx->is_end_mutex);
		ctx->is_end = 1;
		pthread_mutex_unlock(&ctx->is_end_mutex);
		res = 1;
	}
	pthread_mutex_unlock(&ctx->num_eat_mutex);
	return (res);
}

void	*mother_main(void *arg)
{
	t_context	*ctx;
	int			i;

	i = 0;
	ctx = (t_context *)arg;
	pthread_mutex_lock(&ctx->start_mutex);
	pthread_mutex_unlock(&ctx->start_mutex);
	while (get_time(ctx) < 0)
		;
	while (1)
	{
		pthread_mutex_lock(&ctx->philos[i].eat_mutex);
		if (get_time(ctx) - ctx->philos[i].last_eat > ctx->time_to_die)
		{
			print_death(ctx, i);
			break;
		}
		pthread_mutex_unlock(&ctx->philos[i].eat_mutex);
		if (check_eat(ctx))
			break;
		i = (i + 1) % ctx->philo_num;
		usleep(1);
	}
	return (NULL);
}