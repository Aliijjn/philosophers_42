/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 16:48:24 by akuijer       #+#    #+#                 */
/*   Updated: 2024/05/27 14:53:13 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Makes the threads start simultaniously. Always initialise before using

int32_t	is_alive(t_philo *philo)
{
	int32_t	result;

	pthread_mutex_lock(&philo->alive.lock);
	result = philo->alive.info;
	pthread_mutex_unlock(&philo->alive.lock);
	return (result);
}

int64_t	get_set_last_eaten(t_philo *philo, bool set)
{
	int64_t	result;

	result = -1;
	pthread_mutex_lock(&philo->last_eaten.lock);
	if (set)
		philo->last_eaten.info = get_delta_time2(philo);
	else
		result = philo->last_eaten.info;
	pthread_mutex_unlock(&philo->last_eaten.lock);
	return (result);
}

int64_t	ft_strlen(const char *s)
{
	int64_t	i;

	i = 0;
	while (s && s[i])
	{
		i++;
	}
	return (i);
}

void	ft_bzero(void *str, size_t n)
{
	while (n--)
	{
		((char *)str)[n] = 0;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 0;
		size = 0;
	}
	if (nmemb && (size * nmemb) / nmemb != size)
	{
		return (0);
	}
	ptr = malloc(nmemb * size);
	if (!ptr)
	{
		return (0);
	}
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
