/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:10:29 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/11 12:38:38 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *s)
{
	write(2, "Error: ", 7);
	if (!s)
	{
		write(2, "Error: Unknown error\n", 21);
		return (1);
	}
	write(2, s, ft_strlen(s));
	return (1);
}

int	destroy_all(t_locks *l, char *str, int count)
{
	while (count > 0)
	{
		count--;
		pthread_mutex_destroy(&l->forks[count]);
	}
	pthread_mutex_destroy(&l->write_lock);
	pthread_mutex_destroy(&l->meal_lock);
	return (error_msg(str));
}

int	destroy_free(t_locks *l, int count)
{
	while (count > 0)
	{
		count--;
		pthread_mutex_destroy(&l->forks[count]);
	}
	pthread_mutex_destroy(&l->write_lock);
	pthread_mutex_destroy(&l->meal_lock);
	return (0);
}
