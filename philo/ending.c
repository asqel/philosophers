/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:25:51 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/04 22:32:57 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_is_end(t_context *ctx, int val)
{
	pthread_mutex_lock(&ctx->is_end_mutex);
	ctx->is_end = val;
	pthread_mutex_unlock(&ctx->is_end_mutex);
}

int get_is_end(t_context *ctx)
{
	int	val;

	pthread_mutex_lock(&ctx->is_end_mutex);
	val = ctx->is_end;
	pthread_mutex_unlock(&ctx->is_end_mutex);
	return (val);
}
