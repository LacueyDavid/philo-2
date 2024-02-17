/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:38:44 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 08:31:52 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosopher_eat(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork, ssize_t count)
{
	pthread_mutex_lock(first_fork);
	if (is_simulation_over(philo, count))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	if (is_simulation_over(philo, count))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return ;
	}
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->monitor_communication);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->monitor_communication);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return ;
}

static void	philosopher_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	return ;
}

static bool	philosopher_think(t_philo *philo)
{
	int	time;

	print_message(philo, "is thinking");
	if (philo->table->number_of_philosophers % 2 == 0)
		time = philo->table->time_to_eat - philo->table->time_to_sleep - 10;
	else
		time = (2 * philo->table->time_to_eat)
			- philo->table->time_to_sleep - 10;
	if (get_time_in_ms() - philo->last_meal_time + time
		>= philo->table->time_to_die)
		time = 2;
	if (time > 0)
		ft_usleep(time);
	return (false);
}

static void	philo_finish_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor_communication);
	philo->finish_eating = true;
	pthread_mutex_unlock(&philo->monitor_communication);
}

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;
	ssize_t	count;
	ssize_t	max_meal;

	count = 0;
	philo = (t_philo *)arg;
	max_meal = philo->table->times_each_philosopher_must_eat;
	print_message(philo, "is thinking");
	if (philo->id % 2 == 0)
		ft_usleep(2);
	while (max_meal == -1 || count < max_meal)
	{
		if (philo->id % 2 == 0)
			philosopher_eat(philo, philo->left_fork, philo->right_fork, count);
		else
			philosopher_eat(philo, philo->right_fork, philo->left_fork, count);
		count++;
		if (is_simulation_over(philo, count))
			break ;
		philosopher_sleep(philo);
		if (is_simulation_over(philo, count))
			break ;
		philosopher_think(philo);
	}
	return (philo_finish_eating(philo), NULL);
}
