/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:03:16 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/11 13:09:11 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <unistd.h> // usleep
# include <sys/time.h> // gettimeofday
# include <pthread.h> // pthread_create, pthread_detach, pthread_join,  pthread_mutex_init...

# define RESET    "\033[0m"
# define RED      "\033[31m"    /* Red */
# define GREEN    "\033[32m"    /* Green */

typedef struct timeval	t_timeval;

typedef struct	s_data
{
	int		num_of_philo;
	int		num_of_meals;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}	t_data;

typedef struct	s_mutex
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}	t_mutex;

typedef struct	s_philo
{
	t_data		data;
	t_mutex		mutex;
	int			rang_num;
	int			meals_eaten;
	pthread_t	thread_id;
	int			last_meal;
	int			born_time;
}	t_philo;

typedef struct	s_locks
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}	t_locks;

/* utils.c */
int		ft_strlen(char *str);
int		ft_atoi(char *str);
void	ft_usleep(int mls);

/* utils_philo.c */
int		get_current_time(void);
void	print_action(t_philo *p, char *action);

/* errors.c */
int		error_msg(char *s);
int		destroy_all(t_locks *l, char *str, int count);
int		destroy_free(t_locks *l, int count);

/* init.c */
int		init_forks(t_locks	*l, pthread_mutex_t *forks, int count);
void	init_data(t_philo *p, int argc, char **argv);
void	init_philos(t_philo *p, pthread_mutex_t *fork, t_locks *l, char **argv);
int		init_locks(t_locks *l, t_philo *p, pthread_mutex_t *forks);

/* simulation.c */
void	launcher(t_locks *l, int count);

#endif
