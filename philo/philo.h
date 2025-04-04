/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:21:35 by axlleres          #+#    #+#             */
/*   Updated: 2025/04/05 01:45:41 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
#include <stdint.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	unsigned char	is_taken;
}	t_fork;

typedef struct s_context
{
	int				philo_count;
	struct	s_philo	*philos;
	t_fork			*forks;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	pthread_mutex_t is_end_mutex;
	int				is_end;
	int				who_died;
	pthread_mutex_t who_died_mutex;
	pthread_t		mother_thread;
}	t_context;

typedef struct s_philo
{
	t_context		*context;
	int				id;
	pthread_t		thread;
	uint32_t		last_eat;
	int				is_dead;
	int				left;
	int				right;
	int				action;
	pthread_mutex_t action_mutex;
	pthread_mutex_t	has_started;
}	t_philo;

#define PHILO_ACT_EAT		0
#define PHILO_ACT_SLEEP		1
#define PHILO_ACT_THINK		2
#define PHILO_ACT_FORK		3

uint32_t	get_time_ms(int start);

void		set_is_end(t_context *ctx, int val);
int			get_is_end(t_context *ctx);

int			write_error(char *str);
void		philo_print(t_philo *philo);

int			philo_is_dead(t_philo *philo);

int			take_forks(t_philo *philo);
void		leave_fork(t_philo *philo, int idx);
int			try_take_fork(t_philo *philo, int idx);
void		*mother_main(void *arg);
void		*philo_main(void *arg);
int			get_philo_action(t_philo *philo);
void		philo_set_action(t_philo *philo, int action);
int	init_ctx(t_context *ctx);


#endif