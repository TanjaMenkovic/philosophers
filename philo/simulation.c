/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:24:49 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/11 12:52:36 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* checking if all philos have finished eating the required num of meals */
static int	is_all_eaten(t_philo *p)
{
	int		finished;
	int		i;

	i = 0;
	finished = 0;
	if (p[0].data.num_of_meals == -1)
		return (0);
	while (i < p[0].data.num_of_philo)
	{
		pthread_mutex_lock(p->mutex.meal_lock);
		if (p[i].meals_eaten >= p[i].data.num_of_meals)
			finished++;
		pthread_mutex_unlock(p->mutex.meal_lock);
		i++;
	}
	if (finished == p[0].data.num_of_philo)
	{
		pthread_mutex_lock(p->mutex.write_lock);
		return (1);
	}
	return (0);
}

/* observer thread that continuously monitors the state of philosophers. It takes a pointer to a philosopher structure (t_philo *ptr) as input.

Inside an infinite loop, it iterates through each philosopher and checks if any philosopher has exceeded the allowed time without eating (reached the time to die).

If a philosopher is found to have exceeded the allowed time without eating, it prints a message indicating that the philosopher has died, releases the write_lock mutex, and returns NULL to terminate the thread.

If all philosophers have finished eating (as determined by the is_all_eaten function), it returns NULL to terminate the thread. */
static void	*is_died(void *ptr)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)ptr;
	while (1)
	{
		i = -1;
		while (++i < p[0].data.num_of_philo)
		{
			pthread_mutex_lock(p->mutex.meal_lock);
			if (get_current_time() - p[i].last_meal
				> p[i].data.time_to_die)
			{
				pthread_mutex_unlock(p->mutex.meal_lock);
				print_action(&p[i], RED" died"RESET);
				pthread_mutex_lock(p->mutex.write_lock);
				return (NULL);
			}
			pthread_mutex_unlock(p->mutex.meal_lock);
		}
		if (is_all_eaten(p) == 1)
			return (NULL);
	}
	return (NULL);
}

/* This function represents the routine of a philosopher. It takes a pointer to a philosopher structure (t_philo *philo) as input.

The philosopher first locks the mutex of the left fork, then prints a message indicating that it has taken a fork, and similarly for the right fork.

Then, it locks the meal_lock mutex, prints a message indicating that it is eating, updates the last meal time, increments the number of meals eaten, and unlocks the meal_lock mutex.

It then sleeps for the eating time (p->data.time_to_eat), unlocks both forks, and prints messages indicating that it is sleeping and then thinking. */
static void	philo_simulation(t_philo *p)
{
	pthread_mutex_lock(p->mutex.left_fork);
	print_action(p, " has taken a fork");
	pthread_mutex_lock(p->mutex.right_fork);
	print_action(p, " has taken a fork");
	pthread_mutex_lock(p->mutex.meal_lock);
	print_action(p, " is eating");
	p->last_meal = get_current_time();
	p->meals_eaten += 1;
	pthread_mutex_unlock(p->mutex.meal_lock);
	ft_usleep(p->data.time_to_eat);
	pthread_mutex_unlock(p->mutex.left_fork);
	pthread_mutex_unlock(p->mutex.right_fork);
	print_action(p, " is sleeping");
	ft_usleep(p->data.time_to_sleep);
	print_action(p, " is thinking");
}

/* This function represents the starting point of the simulation for a philosopher. It takes a pointer to a philosopher structure (t_philo *ptr) as input.

If the philosopher's rang is even, it sleeps for a short time (1 microsecond).

It then initializes the born time and last meal time of the philosopher and enters an infinite loop where it repeatedly executes the philo_simulation function. */
static void	*start_simulation(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	if (p->rang_num % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(p->mutex.meal_lock);
	p->born_time = get_current_time();
	p->last_meal = get_current_time();
	pthread_mutex_unlock(p->mutex.meal_lock);
	while (1)
		philo_simulation(p);
	return (NULL);
}

/* This function launches the simulation by creating and joining threads for the observer and the philosophers.

It creates a thread for the observer using pthread_create.

It then creates threads for each philosopher using pthread_create.

After creating all threads, it joins the observer thread using pthread_join.

Then, it detaches the threads for each philosopher using pthread_detach. */
void	launcher(t_locks *l, int count)
{
	pthread_t	obsorver_id;
	int		i;

	i = 0;
	if (pthread_create(&obsorver_id, NULL, &is_died, l->philos) != 0)
		destroy_all(l, "Thread Creation failed\n", count);
	while (i < count)
	{
		if (pthread_create(&l->philos[i].thread_id, NULL,
				start_simulation, &l->philos[i]) != 0)
			destroy_all(l, "Thread Creation failed\n", count);
		i++;
	}
	i = 0;
	if (pthread_join(obsorver_id, NULL) != 0)
		destroy_all(l, "Thread Join failed\n", count);
	while (i < count)
	{
		if (pthread_detach(l->philos[i].thread_id) != 0)
			destroy_all(l, "Thread Detach failed\n", count);
		i++;
	}
}
