/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_example.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:47:56 by rsaueia           #+#    #+#             */
/*   Updated: 2024/12/29 18:22:18 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for the usleep library

/* This function simulates work by printing messages and sleeping for 100ms.
It is executed by each thread. */

void    *thread_function(void *arg)
{
    int id;

    id = *(int *)arg;
    printf("Thread %d: Estou executando!\n", id);
	usleep(100000);
	printf("Thread %d: Finalizei meu trabalho.\n", id);
	return (NULL);
}

/* Here, we create and manage threads, ensuring they are all joined before
the program finishes its execution. */

int		main()
{
	int			num_threads;  //number of threads we want to create
	pthread_t	threads[5];  //arrary to store the threads
	int			thread_ids[5]; //IDs that will serve as argument
	int			i;
	
	num_threads = 5;
	i = 0;
	while (i < num_threads)
	{
		thread_ids[i] = i + 1;  //Assign a unique ID to each thread
		if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0)
		{
			perror("Error creating thread.");
			return (1);
		}
		printf("Thread %d foi criada.\n", thread_ids[i]);
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		pthread_join(threads[i], NULL);  // wait for each thread to finish
		printf("Thread %d foi encerrada.\n", i + 1);
		i++;
	}
	printf("Todas as threads foram finalizadas.\n");
	return (0);
}