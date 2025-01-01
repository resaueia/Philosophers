/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:50:30 by rsaueia           #+#    #+#             */
/*   Updated: 2025/01/01 16:37:55 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philosopher *philosopher)
{
	if (philosopher->sim->stop_simulation)
		return ;
	print_message(philosopher, "is currently thinking.");
	ft_usleep(philosopher->sim->time_to_sleep / 2, philosopher->sim);
	//printf("Philosofer %d is currently thinking.\n", philosopher->id);
	//usleep((philosopher->sim->time_to_sleep / 2) * 1000);
	//usleep(15000);
}

void	eat(t_philosopher *philosopher)
{
	if (philosopher->sim->stop_simulation)
		return ;
	if (philosopher->id % 2 == 0)
	{
		//print_left(philosopher, "is attempting to grab fork");
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->left]);
		print_left(philosopher, "has taken fork");
		//print_right(philosopher, "is attempting to grab fork");
		if (pthread_mutex_lock(&philosopher->sim->forks[philosopher->right]) != 0)
		{	
			pthread_mutex_unlock(&philosopher->sim->forks[philosopher->left]);
			return ;
		}
		print_right(philosopher, "has taken fork");
	}
	else
	{	
		//print_right(philosopher, "is attempting to grab fork");
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->right]);
		print_right(philosopher, "has taken fork");
		//print_left(philosopher, "is attempting to grab fork");
		if (pthread_mutex_lock(&philosopher->sim->forks[philosopher->left]) != 0)
		{
			pthread_mutex_unlock(&philosopher->sim->forks[philosopher->right]);
			return ;
		}
		print_left(philosopher, "has taken fork");
	}
		print_message(philosopher, "is eating!");
		//usleep(200000);
		//usleep(philosopher->sim->time_to_eat * 1000);
		ft_usleep(philosopher->sim->time_to_eat, philosopher->sim);
		philosopher->last_meal = current_time();
		pthread_mutex_unlock(&philosopher->sim->forks[philosopher->right]);
		//print_right(philosopher, "has released a fork");
		pthread_mutex_unlock(&philosopher->sim->forks[philosopher->left]);
		//print_left(philosopher, "has released a fork");
}

/*void	eat(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->left]);
		print_left(philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->right]);
		print_right(philosopher, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->right]);
		print_right(philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->left]);
		print_left(philosopher, "has taken a fork");
	}

	print_message(philosopher, "is eating");
	usleep(philosopher->sim->time_to_eat * 1000);
	philosopher->last_meal = current_time();

	pthread_mutex_unlock(&philosopher->sim->forks[philosopher->right]);
	print_right(philosopher, "has released a fork");
	pthread_mutex_unlock(&philosopher->sim->forks[philosopher->left]);
	print_left(philosopher, "has released a fork");
}*/


void	rest(t_philosopher *philosopher)
{
	if (philosopher->sim->stop_simulation)
		return ;
	print_message(philosopher, "is currently sleeping.");
	ft_usleep(philosopher->sim->time_to_sleep, philosopher->sim);
	//printf("Philosopher %d is currently sleeping.\n", philosopher->id);
	//usleep((philosopher->sim->time_to_sleep / 2) * 1000);
	//usleep(15000);
}