/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:06:54 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/11 14:25:50 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* init_input function initializes the t_data structure with input parameters 
passed through the command line arguments argv. It extracts the number of philosophers, 
the time for a philosopher to die, the time for a philosopher to eat, and the time for 
a philosopher to sleep from argv. If the argument count argc is 6, it also extracts the 
number of meals each philosopher must eat. It then returns the initialized t_data structure. */
static t_data	init_input(int argc, char **argv)
{
	t_data	input_data;

	input_data.num_of_philo = ft_atoi(argv[1]);
	input_data.time_to_die = ft_atoi(argv[2]);
	input_data.time_to_eat = ft_atoi(argv[3]);
	input_data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input_data.num_of_meals = ft_atoi(argv[5]);
	else
		input_data.num_of_meals = -1;
	return (input_data);
}

/* init_forks function initializes the mutex locks for forks used by the philosophers. It 
iterates over each fork, initializes the mutex using pthread_mutex_init(), and if any 
initialization fails, it calls destroy_all() to clean up already initialized mutexes and 
returns an error code. */
int	init_forks(t_locks	*l, pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (destroy_all(l, "mutex init\n", i));
		i++;
	}
	return (0);
}

/* init_data function initializes the data for each philosopher. It calls init_input() 
to get the initial data for each philosopher based on command-line arguments. It initializes 
each philosopher's data field with this input data. */
void	init_data(t_philo *p, int argc, char **argv)
{
	int		i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		p[i].data = init_input(argc, argv);
		i++;
	}
}

/* init_philos function initializes the philosopher structures. It sets the philosopher's rank 
number, number of meals eaten, last meal time, and born time. It also assigns the mutex locks 
for the left and right forks, ensuring correct assignment even for edge cases like the first and 
last philosopher. Additionally, it assigns the mutex locks for writing and meal counting. */
void	init_philos(t_philo *p, pthread_mutex_t *fork, t_locks *l, char **argv)
{
	int		i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		p[i].rang_num = i + 1;
		p[i].meals_eaten = 0;
		p[i].last_meal = get_current_time();
		p[i].born_time = get_current_time();
		p[i].mutex.left_fork = &fork[i];
		if (i == 0)
			p[i].mutex.right_fork = &fork[ft_atoi(argv[1]) - 1];
		else
			p[i].mutex.right_fork = &fork[i - 1];
		p[i].mutex.write_lock = &l->write_lock;
		p[i].mutex.meal_lock = &l->meal_lock;
		i++;
	}
}

/* init_locks function initializes the mutex locks for writing and meal counting (write_lock and 
meal_lock), and it assigns the array of forks and philosophers to the corresponding fields in the 
t_locks structure. If any initialization of mutex locks fails, it calls destroy_all() to clean up 
initialized mutexes and returns an error code. */
int	init_locks(t_locks *l, t_philo *p, pthread_mutex_t *forks)
{
	l->forks = forks;
	l->philos = p;
	if (pthread_mutex_init(&l->write_lock, NULL) != 0
			|| pthread_mutex_init(&l->meal_lock, NULL) != 0)
		return (destroy_all(l, "mutex init\n", -1));
	return (0);
}
