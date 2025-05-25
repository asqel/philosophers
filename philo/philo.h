/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:22:46 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/29 14:54:43 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <stdint.h>
#include <pthread.h>

#define PHILO_ACT_FORK "has taken a fork"
#define PHILO_ACT_EAT "is eating"
#define PHILO_ACT_SLEEP "is sleeping"
#define PHILO_ACT_THINK "is thinking"

typedef struct timeval t_timeval;

typedef struct {
	pthread_mutex_t	mutex;
	uint8_t			is_taken;
} t_fork;

typedef struct s_philo {
	int					id;
	t_fork				*left_fork;
	t_fork				*right_fork;
	int64_t				last_eat;
	pthread_mutex_t		eat_mutex;
	struct s_context	*ctx;
} t_philo;

typedef struct s_context {
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat; // -1 = forever
	int				num_eat;
	pthread_mutex_t	num_eat_mutex;
	int				philo_num;

	t_fork			*forks;
	pthread_t		*threads;
	t_philo			*philos;

	pthread_mutex_t	is_end_mutex;
	int 			is_end;

	int64_t			start_time;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	start_mutex;
}	t_context;

int		ft_atoi(char *text, int *res);
int64_t	get_time(t_context *ctx);

int	init_ctx(t_context *ctx, int argc, char **argv);

void	*philo_main(void *arg);
void	*mother_main(void *arg);

void	philo_print(t_philo *philo, char *msg);

int	get_is_end(t_context *ctx);

int	try_take_fork(t_philo *philo, t_fork *fork);
void	leave_fork(t_philo *philo, t_fork *fork);
void	write_error(char *str);

#endif
