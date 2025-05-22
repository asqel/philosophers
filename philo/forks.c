/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:34:48 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/29 14:41:57 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int try_take_fork(t_context *ctx, int fork_id)
{
	pthread_mutex_lock(&ctx->forks[fork_id].mutex);
	if (ctx->forks[fork_id].is_taken == 0)
	{
		ctx->forks[fork_id].is_taken = 1;
		pthread_mutex_unlock(&ctx->forks[fork_id].mutex);
		return (1);
	}
	pthread_mutex_unlock(&ctx->forks[fork_id].mutex);
	return (0);
}

void leave_fork(t_context *ctx, int fork_id)
{
	pthread_mutex_lock(&ctx->forks[fork_id].mutex);
	ctx->forks[fork_id].is_taken = 0;
	pthread_mutex_unlock(&ctx->forks[fork_id].mutex);
}