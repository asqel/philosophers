/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:57:03 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/25 20:54:45 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->ctx->printf_mutex);
	pthread_mutex_lock(&philo->ctx->is_end_mutex);
	if (!philo->ctx->is_end)
		printf("%d %d %s\n", (int)get_time(philo->ctx), philo->id, str);
	pthread_mutex_unlock(&philo->ctx->is_end_mutex);
	pthread_mutex_unlock(&philo->ctx->printf_mutex);
}

void	write_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
}
