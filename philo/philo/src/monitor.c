/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 14:28:08 by akuijer       #+#    #+#                 */
/*   Updated: 2024/08/12 15:04:59 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	end_sim(t_info info, t_philo *philo, int32_t dead_philo)
{
	int32_t	i;

	i = 0;
	while (i < info.philo_count)
	{
		pthread_mutex_lock(&philo[i].alive.lock);
		philo[i].alive.info = false;
		pthread_mutex_unlock(&philo[i].alive.lock);
		i++;
	}
	if (dead_philo)
	{
		printf("%li	%i	has died\n", get_delta_time2(philo) / 1000, philo->id);
	}
}

void	monitor(t_info info, t_philo *philo)
{
	int32_t	i;
	int32_t	lowest_eat;

	while (1)
	{
		i = 0;
		lowest_eat = INT32_MAX;
		while (i < info.philo_count)
		{
			if (!is_alive(&philo[i]) || get_set_last_eaten(&philo[i], 0) \
					+ info.time_to_die * 1000 < get_delta_time2(philo))
				return (end_sim(info, philo, i + 1));
			pthread_mutex_lock(&philo[i].eat_count.lock);
			if (info.max_eat != -1 && philo[i].eat_count.info < lowest_eat)
				lowest_eat = philo[i].eat_count.info;
			pthread_mutex_unlock(&philo[i].eat_count.lock);
			i++;
		}
		if (info.max_eat != -1 && lowest_eat >= info.max_eat)
			return (end_sim(info, philo, 0));
		ft_sleep(200);
	}
}

void	init_monitor(t_info info, t_philo *philo)
{
	int32_t			i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	*philo->start_time = tv_to_micro(time);
	while (i < info.philo_count)
	{
		pthread_mutex_lock(&philo[i].alive.lock);
		philo[i].alive.info = true;
		pthread_mutex_unlock(&philo[i].alive.lock);
		i++;
	}
	ft_sleep(10000);
	monitor(info, philo);
}
