/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_example.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:55:43 by rsaueia           #+#    #+#             */
/*   Updated: 2024/12/29 19:25:41 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int					shared_var = 0;
pthread_mutex_t		mutex;

/* Function carried out by each thread. It increments a shared variable
in a safely manner, by using a mutex. */

void	*thread_function(void *arg)
{
	int	id;
	int	i;
	
	id = *(int *)arg;
	i = 0;
	while (i < 5)
	{
		// Try to access the shared variable
		pthread_mutex_lock(&mutex);
		printf("Thread %d está incrementando a variável.\n", id);
		shared_var++;
		printf("Thread %d terminou. Shared var agora vale %d.\n", id, shared_var);
		pthread_mutex_unlock(&mutex); // Unlock mutex
		usleep(100000); //Simulate a given work/process
		i++;
	}
	return (NULL);
}

/* Here, we create threads to increment the shared variable safely by using a mutex */

int	main(void)
{
	int			num_threads;
	pthread_t	threads[3];
	int			thread_ids[3];
	int			i;

	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		perror("Error initializing mutex");
		return (1);
	}
	num_threads = 3;
	i = 0;
	while (i < num_threads)
	{
		thread_ids[i] = i + 1;
		if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0)
		{
			perror("Error creating thread");
			return (1);
		}
		i++;
	}
	i = -1;
	while (++i < num_threads)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&mutex);
	printf("Todas as threads foram finalizadas. Shared variable valor final: %d\n", shared_var);
	return (0);
}