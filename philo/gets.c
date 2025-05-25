/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:54:30 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/24 22:56:54 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_is_end(t_context *ctx)
{
	int	is_end;

	pthread_mutex_lock(&ctx->is_end_mutex);
	is_end = ctx->is_end;
	pthread_mutex_unlock(&ctx->is_end_mutex);
	return (is_end);
}
