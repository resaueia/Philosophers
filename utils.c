/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:23:44 by rsaueia           #+#    #+#             */
/*   Updated: 2024/12/31 16:03:40 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	current_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				i;

	//i = 0;
	sim = (t_simulation *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->num_philo)
		{
			if (current_time() - sim->philosophers[i].last_meal > sim->time_to_die)
			{
				pthread_mutex_lock(&sim->message_lock);
				printf("Philosopher %d has unfortunately perished!\n", sim->philosophers[i].id);
				pthread_mutex_unlock(&sim->message_lock);
				exit (1);
			}
			i++;
		}
		usleep(1000);
	}
}

void	print_message(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->sim->message_lock);
	printf("Philosopher %d %s\n", philosopher->id, message);
	pthread_mutex_unlock(&philosopher->sim->message_lock);
}