/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 16:44:23 by akuijer       #+#    #+#                 */
/*   Updated: 2024/08/12 15:00:58 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define WHITE "\033[0;37m"

enum e_alive
{
	DEAD = -1,
	IDLE,
	ACTIVE
};

typedef struct t_info
{
	int32_t		philo_count;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	int32_t		max_eat;
}	t_info;

typedef struct t_lock
{
	int64_t			info;
	pthread_mutex_t	lock;
}	t_lock;

typedef struct t_philo
{
	int32_t			id;
	int64_t			*start_time;
	t_lock			last_eaten;
	t_lock			alive;
	t_lock			eat_count;
	pthread_mutex_t	*allow_print;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_info			*info;
}	t_philo;

// Initialisation

t_info			get_input(int argc, char **argv);
t_philo			*init_philos(t_info *info, pthread_mutex_t *fork, \
				int64_t start_time);
pthread_mutex_t	*init_fork(int32_t philo_count);
void			init_monitor(t_info info, t_philo *philo);

// Simulation

void			*simulation_start(void *philo_void);
int64_t			get_set_last_eaten(t_philo *philo, bool set);
int32_t			is_alive(t_philo *philo);
void			printp(char *str, t_philo *philo);

// String shenanigans

int32_t			safe_atoi(char *str);
int64_t			ft_strlen(const char *s);

// Memory management

void			*ft_calloc(size_t nmemb, size_t size);

// Time Management

void			get_delta_time(struct timeval *delta_time);
int64_t			get_delta_time2(t_philo *philo);
void			ft_sleep(int64_t microseconds);
bool			ft_sleep2(int64_t microseconds, t_philo *philo);
int64_t			tv_to_micro(struct timeval data);

// Error management

void			ft_error(char *error_msg, char exit_val);
void			destroy_mutex(pthread_mutex_t *mutex, int32_t len);

#endif
