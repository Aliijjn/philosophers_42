/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 16:44:21 by akuijer       #+#    #+#                 */
/*   Updated: 2024/08/12 15:08:54 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	abort_sim(int32_t philo_count, t_philo *philo, pthread_t *threads)
{
	int32_t	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_lock(&philo[i].alive.lock);
		philo[i].alive.info = -1;
		pthread_mutex_unlock(&philo[i].alive.lock);
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	init_sim(t_info *info, pthread_t *threads, t_philo *philo)
{
	int32_t	i;

	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_create(&threads[i], NULL, simulation_start, &philo[i]))
		{
			ft_error("aborting simulation, pthread_create error", 0);
			abort_sim(i, philo, threads);
			return ;
		}
		i++;
	}
	init_monitor(*info, philo);
	i = 0;
	while (i < info->philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int64_t			start_time;
	t_info			info;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	t_philo			*philo;

	start_time = 0;
	info = get_input(argc, argv);
	thread = ft_calloc(info.philo_count + 1, sizeof(pthread_t));
	fork = init_fork(info.philo_count);
	philo = init_philos(&info, fork, start_time);
	if (!thread || !fork || !philo)
	{
		free(thread);
		destroy_mutex(fork, info.philo_count);
		free(philo);
		ft_error("issue initialising memory", 1);
	}
	init_sim(&info, thread, philo);
	free(thread);
	destroy_mutex(fork, info.philo_count);
	free(philo);
	return (0);
}
