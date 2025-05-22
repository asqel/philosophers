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

typedef struct timeval t_timeval;

#define PHILO_ACT_FORK "has taken a fork"
#define PHILO_ACT_EAT "is eating"
#define PHILO_ACT_SLEEP "is sleeping"
#define PHILO_ACT_THINK "is thinking"

#define MAX_MUTEX 2
#define PH_MUT_PRINTF 0
#define PH_MUT_IS_END 1

typedef struct timeval t_timeval;

typedef struct {
	pthread_mutex_t mutex;
	uint8_t is_taken;
} t_fork;

typedef struct s_context {
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int num_eat;

	int philo_len;
	t_fork *forks;
	pthread_t *threads;
	struct s_philo *philos;

	pthread_mutex_t mutexes[MAX_MUTEX];
	int is_end;
}	t_context;

typedef struct s_philo {
	int id;
	t_timeval last_eat;
	uint8_t is_dead;
	int left_fork;
	int right_fork;
	t_context *ctx;
} t_philo;

int	ft_atoi(char *text, int *res);
t_timeval philo_get_time(int is_start);
t_timeval time_add(t_timeval t, int delay_ms);
int philo_time_is_less(t_timeval t0, t_timeval t1);
void philo_print_death(t_philo *philo);

int philo_is_dead(t_philo *philo);
int get_is_end(t_context *ctx);

int init_ctx(t_context *ctx, int argc, char **argv);


void write_error(char *str);
void write_error_usage(char *name);

void *philo_main(void *arg);

int get_time_ms();

void exit_ctx(t_context *ctx);
void philo_print(t_philo *philo, char *action);
int try_take_fork(t_context *ctx, int fork_id);
void leave_fork(t_context *ctx, int fork_id);

#endif
