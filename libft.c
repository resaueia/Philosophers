/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:57:12 by rsaueia           #+#    #+#             */
/*   Updated: 2025/01/01 17:04:37 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atol(char *nptr)
{
	int			index;
	int			signal;
	long int	number;

	index = 0;
	signal = 1;
	number = 0;
	while ((nptr[index] > 8 && nptr[index] < 14) || nptr[index] == 32)
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			signal *= -1 ;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		number = (number * 10) + (nptr[index] - 48);
		index++;
	}
	number = number * (long int)signal;
	return (number);
}

int			ft_atoi(const char *nptr)
{
	int	index;
	int	signal;
	int	number;

	index = 0;
	signal = 1;
	number = 0;
	while ((nptr[index] > 8 && nptr[index] < 14) || nptr[index] == 32)
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			signal = -signal;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		number = (number * 10) + (nptr[index] - 48);
		index++;
	}
	number = number * signal;
	return (number);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	i = 1;
	while (i <= sim->num_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->message_lock);
	free(sim->forks);
	free(sim->philosophers);
}

void	ft_usleep(long time_in_ms, t_simulation *sim)
{
	long	start;

	start = current_time();
	while (!sim->stop_simulation && (current_time() - start) < time_in_ms)
		usleep(500);
}