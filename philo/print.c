/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:27:38 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/27 11:33:24 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_data(t_data input_data)
{
	printf("Input data:\n");
	printf("Number of philosophers: %d\n", input_data.num_of_philo);
	printf("Time to die: %d\n", input_data.time_to_die);
	printf("Time to eat: %d\n", input_data.time_to_eat);
	printf("Time to sleep: %d\n", input_data.time_to_sleep);
	printf("Number of meals: %d\n", input_data.num_of_meals);
}
