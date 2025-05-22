/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:16:57 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/29 14:31:06 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"

t_timeval	philo_get_time(int is_start)
{
	static t_timeval	start;
	t_timeval			time;

	if (is_start)
		gettimeofday(&start, NULL);

	gettimeofday(&time, NULL);
	time.tv_sec -= start.tv_sec;
	time.tv_usec -= start.tv_usec;
	if (time.tv_usec < 0)
	{
		time.tv_sec--;
		time.tv_usec += 1000000;
	}
	return (time);
}

t_timeval	time_add(t_timeval time, int delay_ms)
{
	time.tv_usec += delay_ms * 1000;
	if (time.tv_usec >= 1000000)
	{
		time.tv_sec += time.tv_usec / 1000000;
		time.tv_usec %= 1000000;
	}
	return (time);
}

int philo_time_is_less(t_timeval t0, t_timeval t1)
{
	if (t0.tv_sec < t1.tv_sec)
		return (1);
	if (t0.tv_sec == t1.tv_sec)
		return t0.tv_usec < t1.tv_usec;
	return (0);
}

int get_time_ms()
{
	t_timeval time;

	time = philo_get_time(0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}