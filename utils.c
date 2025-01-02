/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:23:44 by rsaueia           #+#    #+#             */
/*   Updated: 2025/01/02 19:38:55 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	current_time(t_simulation *sim)
{
	struct timeval	tv;
	long			current;
	
	gettimeofday(&tv, NULL);
	current = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current - sim->start_time);
}

/*void	*monitor(void *arg)
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
			if (current_time(sim) - sim->philosophers[i].last_meal > sim->time_to_die)
			{
				pthread_mutex_lock(&sim->message_lock);
				printf("%ld %d has died.\n", current_time(sim), sim->philosophers[i].id);
				pthread_mutex_unlock(&sim->message_lock);
				sim->stop_simulation = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}*/

void *monitor(void *arg)
{
    t_simulation *sim = (t_simulation *)arg;
    int i;

    while (!sim->stop_simulation)
    {
        i = 0;
        while (i < sim->num_philo)
        {
            if (current_time(sim) - sim->philosophers[i].last_meal > sim->time_to_die)
            {
                pthread_mutex_lock(&sim->message_lock);
                printf("%ld %d has died.\n", current_time(sim), sim->philosophers[i].id);
                sim->stop_simulation = 1;
                pthread_mutex_unlock(&sim->message_lock);
                return NULL;
            }
            i++;
        }
        usleep(500);
    }
    return NULL;
}


void print_message(t_philosopher *philosopher, char *message)
{
    if (philosopher->sim->stop_simulation)
        return;

    pthread_mutex_lock(&philosopher->sim->message_lock);
    printf("%ld %d %s\n", current_time(philosopher->sim), philosopher->id, message);
    pthread_mutex_unlock(&philosopher->sim->message_lock);
}


/*void	print_message(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->sim->message_lock);
	//long int i = current_time();
	//printf("Philosopher %ld %d %s\n", (i / 1000), philosopher->id, message);
	printf("%ld Philosopher %d %s\n", current_time(philosopher->sim), philosopher->id, message);
	pthread_mutex_unlock(&philosopher->sim->message_lock);
}*/

void	print_left(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->sim->message_lock);
	printf("%ld Philosopher %d %s %d (left).\n", current_time(philosopher->sim), philosopher->id, message, philosopher->left);
	pthread_mutex_unlock(&philosopher->sim->message_lock);

}

void	print_right(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->sim->message_lock);
	printf("%ld Philosopher %d %s %d (right).\n", current_time(philosopher->sim), philosopher->id, message, philosopher->right);
	pthread_mutex_unlock(&philosopher->sim->message_lock);
}