/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 17:43:59 by akuijer       #+#    #+#                 */
/*   Updated: 2024/05/24 17:00:19 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int32_t fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

// Exits a process with exit_val.
// Prints error_msg to STDERR and adds an message if errno != 0
void	ft_error(char *error_msg, char exit_val)
{
	ft_putstr_fd(RED, 2);
	if (errno == 0 && error_msg)
	{
		ft_putendl_fd(error_msg, 2);
	}
	else if (error_msg)
	{
		perror(error_msg);
	}
	ft_putstr_fd(WHITE, 2);
	errno = 0;
	if (exit_val)
		exit(exit_val);
}

// destroys all mutexes in a `pthread_mutex_t` array, also frees the array
void	destroy_mutex(pthread_mutex_t *mutex, int32_t len)
{
	int32_t	i;

	i = 0;
	if (!mutex)
	{
		return ;
	}
	while (i < len)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(mutex);
}

// void	destroy_thread(pthread_t *thread, int32_t len)
// {
// 	int32_t	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		pthread_attr_destroy(&thread[i]);
// 		i++;
// 	}
// 	free(thread);
// }
