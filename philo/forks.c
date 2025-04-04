/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:20:46 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/05 01:29:21 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leave_fork(t_philo *philo, int idx)
{
	pthread_mutex_lock(&(philo->context->forks[idx].mutex));
	philo->context->forks[idx].is_taken = 0;
	pthread_mutex_unlock(&(philo->context->forks[idx].mutex));
}

int	try_take_fork(t_philo *philo, int idx)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&(philo->context->forks[idx].mutex));
	if (philo->context->forks[idx].is_taken == 0)
	{
		res = 1;
		philo->context->forks[idx].is_taken = 1;
	}
	pthread_mutex_unlock(&(philo->context->forks[idx].mutex));
	return (res);
}

int take_forks(t_philo *philo)
{
	philo_set_action(philo, PHILO_ACT_THINK);
	while (try_take_fork(philo, philo->left) == 0)
		if (philo_is_dead(philo))
				return 1;
	philo_set_action(philo, PHILO_ACT_FORK);
	if (philo_is_dead(philo))
		return (leave_fork(philo, philo->left), 1);
	while (try_take_fork(philo, philo->right) == 0)
		if (philo_is_dead(philo))
			return (leave_fork(philo, philo->left), 1);
	philo_set_action(philo, PHILO_ACT_FORK);
	if (philo_is_dead(philo))
		return (leave_fork(philo, philo->left), leave_fork(philo, philo->right), 1);
	return (0);
}

void	set_forks(t_philo *philo)
{

	int	left;
	int	right;
	int tmp;

	left = philo->id;
	right = philo->id + 1;
	if (right == philo->context->philo_count)
		right = 0;

	if (philo->id % 2)
	{
		tmp = left;
		left = right;
		right = tmp;
	}
	philo->right = right;
	philo->left = left;
}
