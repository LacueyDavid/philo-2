/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:50:54 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 02:39:46 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef MAX_PHILOS
#  define MAX_PHILOS 200
# endif

# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

struct	s_table;

typedef struct s_philo
{
	size_t			id;
	size_t			max_meals;
	bool			finish_eating;
	pthread_mutex_t	monitor_communication;
	bool			someone_died;
	size_t			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	size_t			dinner_start_time;
	size_t			number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	ssize_t			times_each_philosopher_must_eat;
	pthread_mutex_t	forks[MAX_PHILOS];
	t_philo			philos[MAX_PHILOS];
}	t_table;

bool	check_arguments_validity(int argc, char **argv);

bool	ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		ft_strlen(const char *s);

bool	prepare_the_table(t_table *table, int argc, char **argv);
bool	philos_take_their_seats(t_table *table);

void	clean_the_table(t_table *table, size_t size_to_clean);

bool	start_the_dinner(t_table *table);

void	*philosophers_routine(void *arg);

size_t	get_time_in_ms(void);

void	ft_usleep(size_t time_in_ms);

void	print_message(t_philo *philo, char *message);

bool	is_the_meal_over(t_philo *philo);

#endif
