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

static void	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		error_msg("incorrect number of arguments!\n");
	if (ft_atoi(argv[1]) < 1)
		error_msg("needed at least 1 philosopher!\n");
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0
		|| (ft_atoi(argv[5]) < 0 && argc == 6))
		error_msg("input must be positive numbers!\n");
}

int	main(int argc, char **argv)
{
	t_philo	*p;

	check_args(argc, argv);
	p = malloc(sizeof(t_philo) * ft_argv[1]);
	init_philos(p, argc, argv);
//	print_data(input_data);
	return (0);
}
