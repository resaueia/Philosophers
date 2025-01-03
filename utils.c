/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:23:44 by rsaueia           #+#    #+#             */
/*   Updated: 2025/01/03 18:09:37 by rsaueia          ###   ########.fr       */
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
    t_simulation	*sim;
    int 			i;
	//int				meals_finished;
	int				all_meals_completed;
	
	sim = (t_simulation *)arg;
	i = 0;
    while (!sim->stop_simulation)
    {
		i = 0;
		//meals_finished = 1;
		all_meals_completed = 1;       
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
			if (sim->meals_required != -1 && sim->philosophers[i].meals_eaten < sim->meals_required)
				all_meals_completed = 0;
            i++;
        }
		if (sim->meals_required != -1 && all_meals_completed)
			{
				pthread_mutex_lock(&sim->message_lock);
				printf("All philosophers have eaten at least %d times.\n", sim->meals_required);
				sim->stop_simulation = 1;
				pthread_mutex_unlock(&sim->message_lock);
				return (NULL);
			}
        usleep(100);
    }
    return NULL;
}

/*void	*supervisor(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (!philosopher->sim->stop_simulation)
	{
		pthread_mutex_lock(&philosopher->lock);
		if (current_time(philosopher->sim) - philosopher->last_meal > philosopher->time_to_die)
		{
			pthread_mutex_lock(&philosopher->sim->message_lock);
			printf("%ld %d has died. \n", current_time(philosopher->sim), philosopher->id);
			philosopher->sim->stop_simulation = 1;
			pthread_mutex_unlock(&philosopher->sim->message_lock);
			pthread_mutex_unlock(&philosopher->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philosopher->lock);
		usleep(500);
	}
	return (NULL);
}*/


void	print_message(t_philosopher *philosopher, char *message)
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