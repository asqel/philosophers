/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:27:03 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/29 14:43:49 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void philo_print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->ctx->mutexes[PH_MUT_PRINTF]);
	if (get_is_end(philo->ctx) == 0)
		printf("%u %d %s\n", get_time_ms(), philo->id, action);
	pthread_mutex_unlock(&philo->ctx->mutexes[PH_MUT_PRINTF]);
}

void write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
}

void write_error_usage(char *name)
{
	// name <num_philos> <time_to_die> <time_to_eat> <time_to_sleep> [num_eat]
	write_error("Usage: ");
	write_error(name);
	write_error(" <num_philos> <time_to_die> <time_to_eat> <time_to_sleep> [num_eat]\n");
}