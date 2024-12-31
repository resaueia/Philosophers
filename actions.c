/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:50:30 by rsaueia           #+#    #+#             */
/*   Updated: 2024/12/31 18:00:15 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philosopher *philosopher)
{
	print_message(philosopher, "is currently thinking.");
	//printf("Philosofer %d is currently thinking.\n", philosopher->id);
	usleep(philosopher->sim->time_to_sleep * 1000);
}

void	eat(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		print_left(philosopher, "is attempting to grab fork");
		//printf("Philosopher %d is attempting to grab fork %d (left).\n", philosopher->id, philosopher->left);
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->left]);
		print_left(philosopher, "has taken a fork");
		//printf("Philosopher %d has taken fork %d (left).\n", philosopher->id, philosopher->left);
		print_right(philosopher, "is attempting to grab fork");
		//printf("Philosopher %d is attempting to grab fork %d (right).\n", philosopher->id, philosopher->right);
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->right]);
		print_right(philosopher, "has taken a fork");
		//printf("Philosopher %d has taken fork %d (right).\n", philosopher->id, philosopher->right);
	}
	else
	{	
		print_right(philosopher, "is attempting to grab fork");
		//printf("Philosopher %d is attempting to grab fork %d (right).\n", philosopher->id, philosopher->right);
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->right]);
		print_right(philosopher, "has taken a fork");
		//printf("Philosopher %d has taken fork %d (right).\n", philosopher->id, philosopher->right);
		print_left(philosopher, "is attempting to grab fork");
		//printf("Philosopher %d is attempting to grab fork %d (left).\n", philosopher->id, philosopher->left);
		pthread_mutex_lock(&philosopher->sim->forks[philosopher->left]);
		print_left(philosopher, "has taken a fork");
		//printf("Philosopher %d has taken fork %d (left).\n", philosopher->id, philosopher->left);
	}
		print_message(philosopher, "is eating!");
		//printf("Philosopher %d is having a feast!\n", philosopher->id);
		usleep(200000);
		philosopher->last_meal = current_time();
		pthread_mutex_unlock(&philosopher->sim->forks[philosopher->right]);
		print_right(philosopher, "has released a fork");
		//printf("Philosopher %d has released fork %d (right).\n", philosopher->id, philosopher->right);
		pthread_mutex_unlock(&philosopher->sim->forks[philosopher->left]);
		print_left(philosopher, "has released a fork");
		//printf("Philosopher %d has released fork %d (left).\n", philosopher->id, philosopher->left);
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
	print_message(philosopher, "is currently sleeping.");
	//printf("Philosopher %d is currently sleeping.\n", philosopher->id);
	usleep(philosopher->sim->time_to_sleep * 1000);
}