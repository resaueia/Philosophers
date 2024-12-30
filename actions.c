/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:50:30 by rsaueia           #+#    #+#             */
/*   Updated: 2024/12/30 20:10:52 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philosopher *philosopher)
{
	printf("Philosofer %d is currently thinking.\n", philosopher->id);
	usleep(100000);
}

void	eat(t_philosopher *philosopher)
{
	printf("Philosopher %d is attempting to grab fork %d (left).\n", philosopher->id, philosopher->left);
	pthread_mutex_lock(&philosopher->sim->forks[philosopher->left]);
	printf("Philosopher %d has taken fork %d (left).\n", philosopher->id, philosopher->left);
	printf("Philosopher %d is attempting to grab fork %d (right).\n", philosopher->id, philosopher->right);
	pthread_mutex_lock(&philosopher->sim->forks[philosopher->right]);
	printf("Philosopher %d has taken fork %d (right).\n", philosopher->id, philosopher->right);
	printf("Philosopher %d is having a feast!\n", philosopher->id);
	usleep(200000);
	pthread_mutex_unlock(&philosopher->sim->forks[philosopher->right]);
	printf("Philosopher %d has released fork %d (right).\n", philosopher->id, philosopher->right);
	pthread_mutex_unlock(&philosopher->sim->forks[philosopher->left]);
	printf("Philosopher %d has released fork %d (left).\n", philosopher->id, philosopher->left);
}

void	rest(t_philosopher *philosopher)
{
	printf("Philosopher %d is currently sleeping.\n", philosopher->id);
	usleep(150000);
}