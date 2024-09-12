/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 14:08:31 by akuijer       #+#    #+#                 */
/*   Updated: 2024/05/27 15:49:54 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	printp(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->allow_print);
	if (is_alive(philo))
		printf("%li	%i	%s\n", get_delta_time2(philo) / 1000, philo->id, str);
	pthread_mutex_unlock(philo->allow_print);
}

void	take_forks(t_philo *philo)
{
	if (philo->info->philo_count == 1)
	{
		ft_sleep2(philo->info->time_to_die * 1000, philo);
		pthread_exit(NULL);
	}
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	if (is_alive(philo) == false)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_exit(NULL);
	}
	printp("has taken a fork", philo);
	printp("has taken a fork", philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	simulation_loop(t_info *info, t_philo *philo)
{
	printp("is thinking", philo);
	if (philo->id % 2)
		ft_sleep(40000);
	while (is_alive(philo))
	{
		take_forks(philo);
		printp("is eating", philo);
		get_set_last_eaten(philo, 1);
		if (ft_sleep2(info->time_to_eat * 1000, philo) == false)
			return (drop_forks(philo));
		if (info->max_eat != -1)
		{
			pthread_mutex_lock(&philo->eat_count.lock);
			philo->eat_count.info++;
			pthread_mutex_unlock(&philo->eat_count.lock);
		}
		drop_forks(philo);
		if (!is_alive(philo))
			return ;
		printp("is sleeping", philo);
		ft_sleep2(info->time_to_sleep * 1000, philo);
		if (is_alive(philo))
			printp("is thinking", philo);
	}
}

void	*simulation_start(void *philo_void)
{
	t_philo	*philo;
	int32_t	result;

	philo = philo_void;
	while (1)
	{
		result = is_alive(philo);
		if (result == 1)
			break ;
		else if (result == -1)
			return (NULL);
		ft_sleep(100);
	}
	simulation_loop(philo->info, philo);
	return (NULL);
}
