/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:10:29 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/29 10:43:07 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *s)
{
	write(2, "Error: ", 7);
	if (!s)
	{
		write(2, "Error: Unknown error\n", 21);
		exit(1);
	}
	write(2, s, ft_strlen(s));
	exit(1);
}
