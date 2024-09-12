/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 17:07:29 by akuijer       #+#    #+#                 */
/*   Updated: 2024/05/27 15:33:19 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Makes your programme wait for the imput amount of microsec
void	ft_sleep(int64_t microsec)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	while (tv_to_micro(current) - tv_to_micro(start) < microsec - 100)
	{
		usleep((microsec - (tv_to_micro(current) - tv_to_micro(start))) / 2);
		gettimeofday(&current, NULL);
	}
	while (tv_to_micro(current) - tv_to_micro(start) < microsec)
	{
		usleep(100);
		gettimeofday(&current, NULL);
	}
}

// Same as `ft_sleep`, also monitors the status of the philosopher
bool	ft_sleep2(int64_t microsec, t_philo *philo)
{
	int64_t	start;

	start = get_delta_time2(philo);
	if (get_set_last_eaten(philo, 0) + philo->info->time_to_die * 1000 + 3 \
			> start + microsec)
	{
		ft_sleep(microsec);
		return (true);
	}
	while (get_delta_time2(philo) - start < microsec)
	{
		if (get_set_last_eaten(philo, 0) + philo->info->time_to_die * 1000 \
				< get_delta_time2(philo))
		{
			pthread_mutex_lock(&philo->alive.lock);
			philo->alive.info = false;
			pthread_mutex_unlock(&philo->alive.lock);
			return (false);
		}
		usleep(100);
	}
	return (true);
}

int64_t	get_delta_time2(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (tv_to_micro(time) - *philo->start_time);
}

// Initialise this function with delta = NULL.
// Delta becomes the difference in time between
// initialisation and when the function is called
// void	get_delta_time(struct timeval *delta)
// {
// 	static struct timeval	start;
// 	struct timeval			current;

// 	if (delta == NULL)
// 	{
// 		gettimeofday(&start, NULL);
// 		return ;
// 	}
// 	gettimeofday(&current, NULL);
// 	delta->tv_sec =  current.tv_sec -  start.tv_sec;
// 	delta->tv_usec = current.tv_usec - start.tv_usec;
// }

// Converts a timeval struct to microsec (1/1,000,000 second)
int64_t	tv_to_micro(struct timeval data)
{
	return (data.tv_sec * 1000000 + data.tv_usec);
}
