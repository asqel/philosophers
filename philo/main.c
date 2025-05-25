/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 01:29:16 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/25 01:29:16 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "philo.h"

int	main(int argc, char **argv) {
	t_context	ctx;
	int			i;

	if (init_ctx(&ctx, argc, argv))
		return (1);
	i = 0;
	while (i < ctx.philo_num + 1)
		pthread_join(ctx.threads[i++], NULL);
	free(ctx.philos);
	free(ctx.forks);
	free(ctx.threads);
	return (0);
}
