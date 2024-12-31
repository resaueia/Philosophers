/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:17:19 by rsaueia           #+#    #+#             */
/*   Updated: 2024/12/31 16:05:48 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	philosopher->last_meal = current_time();
	while (1)
	{
		think(philosopher);
		eat(philosopher);
		rest(philosopher);
	}
}

int		main(void)
{
	t_simulation	simulation;
	pthread_t		monitor_thread;
	int				i;
	
	i = 0;
	simulation.time_to_die = 1000;
	init_simulation(&simulation, 5);
	if (pthread_create(&monitor_thread, NULL, monitor, &simulation) != 0)
	{
		perror("Error creating monitor thread");
		exit (1);
	}
	start_simulation(&simulation);
	sleep(3);
	printf("Ending simulation.\n");
	while (i < simulation.num_philo)
	{
		pthread_cancel(simulation.philosophers[i].thread);
		pthread_join(simulation.philosophers[i].thread, NULL);
		i++;
	}
	pthread_cancel(monitor_thread);
    pthread_join(monitor_thread, NULL);
	i = -1;
	while (++i < simulation.num_philo)
	{
		pthread_mutex_destroy(&simulation.forks[i]);
		pthread_mutex_destroy(&simulation.message_lock);
	}
	free(simulation.forks);
	free(simulation.philosophers);
	return (0);
}