/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:43:58 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/09 16:03:19 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* get_current_time function uses gettimeofday() to get the current time in microseconds and then 
converts it to milliseconds before returning the result. */
int	get_current_time(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_msg("gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* print_action function prints an action performed by a philosopher (p) along with a timestamp. 
It acquires a lock on the write mutex to ensure thread safety while printing, gets the current 
time using get_current_time(), calculates the time difference between the current time and the 
philosopher's born_time, and then prints the action along with the timestamp. */
void	print_action(t_philo *p, char *action)
{
	size_t	time;

	pthread_mutex_lock(p->mutex.write_lock);
	time = get_current_time() - p->born_time;
	printf(GREEN"[%ld]"RESET" %d%s\n", time, p->rang_num, action);
	pthread_mutex_unlock(p->mutex.write_lock);
}

/* ft_usleep function mimics the behavior of usleep() but in milliseconds. It gets the current time 
before entering a loop where it repeatedly checks if the elapsed time since start (obtained using 
get_current_time()) is less than the specified mls (milliseconds). Inside the loop, it calls usleep(500) 
to pause the execution for a short duration. This loop continues until the desired milliseconds have passed. */
void	ft_usleep(int mls)
{
	int	start;

	start = get_current_time();
	while (get_current_time() - start < mls)
		usleep(500);
}
