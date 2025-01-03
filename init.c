/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:48:49 by rsaueia           #+#    #+#             */
/*   Updated: 2025/01/01 17:26:58 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_simulation(t_simulation *sim, int num_philo)
{
	int				i;
	struct timeval	tv;
	

	i = 0;
	gettimeofday(&tv, NULL);
	sim->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	sim->num_philo = num_philo;
	sim->forks = malloc(num_philo * sizeof(pthread_mutex_t));
	if (!sim->forks)
	{
		perror("Error creating forks");
		exit (1);
	}
	while (i < num_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			perror("Error initializing fork mutex");
			exit (1);
		}
		if (pthread_mutex_init(&sim->message_lock, NULL) != 0)
		{
			perror("Error initializinh message mutex");
			exit (1);
		}
		i++;
	}
	sim->philosophers = malloc(num_philo * sizeof(t_philosopher));
	if (!sim->philosophers)
	{
		perror("Error allocating memory for philosophers");
		exit (1);
	}
	i = 0;
	while (i < num_philo)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].left = i;
		sim->philosophers[i].right = (i + 1) % num_philo;
		sim->philosophers[i].sim = sim;  // this is so the cycle is properly closed given a round table
		sim->philosophers[i].last_meal = current_time(sim);
		i++;
	}
}

void	start_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_create(&sim->philosophers[i].thread, NULL, philosopher_routine, &sim->philosophers[i]) != 0)
		{
			perror("Error creating philosopher thread");
			exit (1);
		}
		i++;
	}
}