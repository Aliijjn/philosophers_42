/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_atoi.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 14:34:47 by akuijer       #+#    #+#                 */
/*   Updated: 2024/05/24 15:54:55 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int64_t	ft_atol(char *str)
{
	int32_t	i;
	int64_t	nbr;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr);
}

bool	is_number(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// Checks if a string consists only of numbers, that combined fit in int32_t
int32_t	safe_atoi(char *str)
{
	int64_t	nbr;

	if (!is_number(str))
	{
		ft_error("Invalid input: Not a valid positive number", 1);
	}
	nbr = ft_atol(str);
	if (ft_strlen(str) > 10 || nbr > INT32_MAX)
	{
		ft_error("Invalid input: number shouldn't exceed INT32_MAX", 1);
	}
	return (nbr);
}
