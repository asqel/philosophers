/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:00:11 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/05 01:40:21 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_philo_action(t_philo *philo)
{
	int	action;

	pthread_mutex_lock(&philo->action_mutex);
	action = philo->action;
	pthread_mutex_unlock(&philo->action_mutex);
	return (action);
}

void philo_set_action(t_philo *philo, int action)
{
	while (get_philo_action(philo) != -1 && get_philo_action(philo) != PHILO_ACT_THINK)
	{
		if (philo_is_dead(philo))
			return ;
	}
	pthread_mutex_lock(&philo->action_mutex);
	philo->action = action;
	pthread_mutex_unlock(&philo->action_mutex);
}
