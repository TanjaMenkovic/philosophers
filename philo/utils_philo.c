/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:43:58 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/06 15:11:35 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_time(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_msg("gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_action(t_philo *p, char *action)
{
	size_t	time;

	pthread_mutex_lock(p->mutex.write_lock);
	time = get_current_time() - p->born_time;
	printf(GREEN"[%ld]"RESET" %d%s\n", time, p->rang_num, action);
	pthread_mutex_unlock(p->mutex.write_lock);
}

void	ft_usleep(int mls)
{
	int	start;

	start = get_current_time();
	while (get_current_time() - start < mls)
		usleep(500);
}
