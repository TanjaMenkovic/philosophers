/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:06:54 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/29 11:00:22 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	init_forks(t_locks	*l, pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (destroy_all(l, "[Mutex Init ERROR]\n", i, 1));
		i++;
	}
	return (0);
}

t_philo	*init_philos(pthread_mutex_t *forks, t_locks *l, int argc, char **argv)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		p[i].data = init_input(argc, argv);
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

int	init_locks(t_locks *l, t_philo *p, pthread_mutex_t *forks)
{
	l->forks = forks;
	l->philos = p;
	if (pthread_mutex_init(&l->write_lock, NULL) != 0
			|| pthread_mutex_init(&l->meal_lock, NULL) != 0)
		return (destroy_all(l, "[Mutex Init ERROR]\n", -1, 1));
	return (0);
}
