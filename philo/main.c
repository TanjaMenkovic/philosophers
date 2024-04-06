/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:06:28 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/29 11:00:24 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_msg("incorrect number of arguments!\n", 1));
	if (ft_atoi(argv[1]) < 1)
		return (error_msg("needed at least 1 philosopher!\n", 1));
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0
		|| (ft_atoi(argv[5]) < 0 && argc == 6))
		return (error_msg("input must be positive numbers!\n"), 1);
}

int	main(int argc, char **argv)
{
	t_philo			*p;
	pthread_mutex_t	*forks;
	t_locks			l;

	if (check_args(argc, argv) == 1)
		return (1);
	p = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!p)
		return (error_msg("Failed to malloc philosophers!\n", 1));
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!forks)
	{
		free(p);
		return (error_msg("Failed to malloc forks!\n", 1));
	}
	if (init_locks(&l, p, forks) != 0)
	{
		free(p);
		free(forks);
		return (1);
	}
	if (init_forks(&l, forks, ft_atoi(argv[1])) != 0)
	{
		free(p);
		free(forks);
		return (1);
	}
	init_philos(p, forks, &l, argc, argv);

	return (0);
}
