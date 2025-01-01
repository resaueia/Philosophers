/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:23:44 by rsaueia           #+#    #+#             */
/*   Updated: 2025/01/01 16:29:59 by rsaueia          ###   ########.fr       */
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
	while (!sim->stop_simulation)
	{
		i = 0;
		while (i < sim->num_philo)
		{
			if (current_time() - sim->philosophers[i].last_meal > sim->time_to_die)
			{
				pthread_mutex_lock(&sim->message_lock);
				printf("%ld %d has died.\n", current_time(), sim->philosophers[i].id);
				pthread_mutex_unlock(&sim->message_lock);
				sim->stop_simulation = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	print_message(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->sim->message_lock);
	//long int i = current_time();
	//printf("Philosopher %ld %d %s\n", (i / 1000), philosopher->id, message);
	if (!philosopher->sim->stop_simulation)
		printf("%ld Philosopher %d %s\n", current_time(), philosopher->id, message);
	pthread_mutex_unlock(&philosopher->sim->message_lock);
}

void	print_left(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->sim->message_lock);
	printf("%ld Philosopher %d %s %d (left).\n", current_time(), philosopher->id, message, philosopher->left);
	pthread_mutex_unlock(&philosopher->sim->message_lock);

}

void	print_right(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->sim->message_lock);
	printf("%ld Philosopher %d %s %d (right).\n", current_time(), philosopher->id, message, philosopher->right);
	pthread_mutex_unlock(&philosopher->sim->message_lock);
}