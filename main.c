/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:17:19 by rsaueia           #+#    #+#             */
/*   Updated: 2025/01/02 20:08:32 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	philosopher->last_meal = current_time(philosopher->sim);
	while (!philosopher->sim->stop_simulation)
	{
		if (philosopher->sim->stop_simulation)
			break ;
		think(philosopher);
		if (philosopher->sim->stop_simulation)
			break ;
		eat(philosopher);
		if (philosopher->sim->stop_simulation)
			break ;
		rest(philosopher);
	}
	return (NULL);
}

int	validate_args(int argc, char **argv, t_simulation *sim)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: The number of arguments is inavlid.\n"
				"Try the following format: ./philo 5 800 200 200\n");
		return (1);
	}
	sim->num_philo = ft_atoi(argv[1]);
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	if (sim->num_philo <= 0 || sim->time_to_die <= 0 || sim->time_to_eat <= 0
		|| sim->time_to_sleep <= 0)
	{
		printf("Error: Arguments must be positive numbers, larger than zero.\n");
		return (1);
	}
	return (0);
}

/*int	main(int argc, char **argv)
{
	t_simulation simulation;
	pthread_t monitor_thread;
	int i;

	if (validate_args(argc, argv, &simulation))
		return (1);
	init_simulation(&simulation, simulation.num_philo);
	simulation.stop_simulation = 0;
	if (pthread_create(&monitor_thread, NULL, monitor, &simulation) != 0)
	{
		perror("Error creating monitor thread");
		cleanup_simulation(&simulation);
		exit(1);
	}
	start_simulation(&simulation);
	sleep(3);
	pthread_mutex_lock(&simulation.message_lock);
	printf("Ending simulation.\n");
	pthread_mutex_unlock(&simulation.message_lock);
	i = 0;
	while (i < simulation.num_philo)
		pthread_join(simulation.philosophers[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	cleanup_simulation(&simulation);
	return (0);
}*/

/*int main(int argc, char **argv)
{
    t_simulation simulation;
    pthread_t monitor_thread;

    if (validate_args(argc, argv, &simulation))
        return (1);

    init_simulation(&simulation, simulation.num_philo);
    simulation.stop_simulation = 0;

    if (pthread_create(&monitor_thread, NULL, monitor, &simulation) != 0)
    {
        perror("Error creating monitor thread");
        cleanup_simulation(&simulation);
        exit(1);
    }

    start_simulation(&simulation);

    pthread_join(monitor_thread, NULL);
    for (int i = 0; i < simulation.num_philo; i++)
        pthread_join(simulation.philosophers[i].thread, NULL);

    cleanup_simulation(&simulation);
    return 0;
}*/

int		main(int argc, char **argv)
{
	t_simulation	simulation;
	pthread_t		monitor_thread;
	int				i;
	
	if (validate_args(argc, argv, &simulation))
		return (1);
	init_simulation(&simulation, simulation.num_philo);
	simulation.stop_simulation = 0;
	if (pthread_create(&monitor_thread, NULL, monitor, &simulation) != 0)
	{
		perror("Error creating monitor thread");
		cleanup_simulation(&simulation);
		exit (1);
	}
	start_simulation(&simulation);
	//sleep(3);
	pthread_mutex_lock(&simulation.message_lock);
	printf("Ending simulation.\n");
	pthread_mutex_unlock(&simulation.message_lock);
	i = 0;
	/*while (i < simulation.num_philo)
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
	free(simulation.philosophers);*/
	while (++i < simulation.num_philo)
		pthread_join(simulation.philosophers[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	cleanup_simulation(&simulation);
	return (0);
}
