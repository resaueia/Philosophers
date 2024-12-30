/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:21:59 by rsaueia           #+#    #+#             */
/*   Updated: 2024/12/30 20:08:55 by rsaueia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* This struct represents each philosopher and it carries their IDs,
their left and right forks (mutexes) and their associated threads. */

typedef struct s_philosopher
{
	int					id;
	int					left;
	int					right;
	pthread_t			thread;
	struct s_simulation	*sim;
} t_philosopher;

/* This struct represents the dining simulation as a whole and it carries
the number of philosophers, their forks (a mutexes array where each mutex represents
a fork) and the philosophers present (an array of t_philosopher structs) */

typedef struct s_simulation
{
	int					num_philo;
	pthread_mutex_t		*forks;  //mutexes array
	t_philosopher		*philosophers;  //philosophers array
} t_simulation;

/***** ACTIONS *****/
void	think(t_philosopher *philosopher);
void	eat(t_philosopher *philosopher);
void	rest(t_philosopher *philosopher);

/***** INITIALIZING FUNCTIONS *****/
void	init_simulation(t_simulation *sim, int num_philo);
void	start_simulation(t_simulation *sim);

/***** BEHAVIORAL FUNCTIONS *****/
void	*philosopher_routine(void *arg);

#endif 