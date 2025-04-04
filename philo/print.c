/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:15:23 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/05 01:43:13 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	philo_print(t_philo *philo)
{
	struct timeval	now;

	if (get_is_end(philo->context) == 1)
		return ;
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->action_mutex);
	if (philo->action == PHILO_ACT_EAT)
		printf("%u %d is eating\n", get_time_ms(0), philo->id + 1);
	else if (philo->action == PHILO_ACT_SLEEP)
		printf("%u %d is sleeping\n", get_time_ms(0), philo->id + 1);
	else if (philo->action == PHILO_ACT_THINK)
		printf("%u %d is thinking\n", get_time_ms(0), philo->id + 1);
	else if (philo->action == PHILO_ACT_FORK)
		printf("%u %d has taken a fork\n", get_time_ms(0), philo->id + 1);
	philo->action = -1;
	pthread_mutex_unlock(&philo->action_mutex);
}

int	write_error(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
		len++;
	write(STDERR_FILENO, str, len);
	return (1);
}
