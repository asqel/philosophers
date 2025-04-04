/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:16:00 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/05 01:35:39 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if start set start
uint32_t get_time_ms(int start)
{
	static struct timeval	start_time;
	static struct timeval	now;
	long long int			time_tmp[2];

	if (start)
		gettimeofday(&start_time, NULL);

	gettimeofday(&now, NULL);
	time_tmp[0] = now.tv_sec;
	time_tmp[1] = now.tv_usec;
	time_tmp[0] -= start_time.tv_sec;
	time_tmp[1] -= start_time.tv_usec;
	while (time_tmp[1] < 0)
	{
		time_tmp[0]--;
		time_tmp[1] += 1000000;
	}
	return (time_tmp[0] * 1000 + time_tmp[1] / 1000);
}
