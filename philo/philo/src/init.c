/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 14:36:30 by akuijer       #+#    #+#                 */
/*   Updated: 2024/08/12 15:08:08 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_info	get_input(int argc, char **argv)
{
	t_info	result;

	if (argc != 5 && argc != 6)
	{
		ft_error("Argc should be 5 or 6!", 1);
	}
	result.philo_count = safe_atoi(argv[1]);
	if (result.philo_count == 0)
	{
		ft_error("Philo count should be at least 1!", 1);
	}
	result.time_to_die = safe_atoi(argv[2]);
	result.time_to_eat = safe_atoi(argv[3]);
	result.time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
	{
		result.max_eat = safe_atoi(argv[5]);
	}
	else
	{
		result.max_eat = -1;
	}
	return (result);
}

t_philo	*init_philos(t_info *info, pthread_mutex_t *fork, int64_t start_time)
{
	int32_t					i;
	t_philo					*philo;
	static pthread_mutex_t	allow_print;

	i = 0;
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(&allow_print, NULL))
		return (NULL);
	philo = ft_calloc(info->philo_count, sizeof(t_philo));
	if (!philo)
		return (NULL);
	while (i < info->philo_count)
	{
		philo[i] = (t_philo){i + 1, &start_time, (t_lock){.info = 0}, \
				(t_lock){.info = false}, (t_lock){.info = 0}, &allow_print, \
				&fork[i], &fork[(i + 1) % info->philo_count], info};
		if (pthread_mutex_init(&philo[i].last_eaten.lock, NULL) != 0 \
			|| pthread_mutex_init(&philo[i].alive.lock, NULL) != 0 \
			|| pthread_mutex_init(&philo[i].eat_count.lock, NULL) != 0)
			return (free(philo), NULL);
		i++;
	}
	return (philo);
}

pthread_mutex_t	*init_fork(int32_t philo_count)
{
	int32_t			i;
	pthread_mutex_t	*fork_array;

	i = 0;
	fork_array = ft_calloc(philo_count, sizeof(pthread_mutex_t));
	if (!fork_array)
	{
		return (NULL);
	}
	while (i < philo_count)
	{
		pthread_mutex_init(&fork_array[i], NULL);
		i++;
	}
	return (fork_array);
}
