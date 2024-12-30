/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:17:19 by rsaueia           #+#    #+#             */
/*   Updated: 2024/12/30 20:09:18 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
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
	int				i;
	
	i = 0;
	init_simulation(&simulation, 5);
	start_simulation(&simulation);
	sleep(3);
	printf("Ending simulation.\n");
	while (i < simulation.num_philo)
	{
		pthread_cancel(simulation.philosophers[i].thread);
		pthread_join(simulation.philosophers[i].thread, NULL);
		i++;
	}
	i = -1;
	while (++i < simulation.num_philo)
		pthread_mutex_destroy(&simulation.forks[i]);
	free(simulation.forks);
	free(simulation.philosophers);
	return (0);
}