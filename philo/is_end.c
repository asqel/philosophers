/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:12:01 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/29 14:17:49 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_is_end(t_context *ctx)
{
	int is_end;

	pthread_mutex_lock(&ctx->mutexes[PH_MUT_IS_END]);
	is_end = ctx->is_end;
	pthread_mutex_unlock(&ctx->mutexes[PH_MUT_IS_END]);
	return (is_end);
}
