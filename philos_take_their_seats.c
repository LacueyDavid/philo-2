/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_take_their_seats.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:33:22 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 04:11:21 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_mutexes_number_of_meals(t_philo *philo, int index)
{
	while (index >= 0)
	{
		pthread_mutex_destroy(&philo[index].monitor_communication);
		index--;
	}
}

static bool	assign_data_to_philo(t_philo *philo, int number_of_philos,
				pthread_mutex_t *forks)
{
	int	index;

	index = 0;
	while (index < number_of_philos)
	{
		philo[index].last_meal_time = get_time_in_ms();
		philo[index].id = index + 1;
		philo[index].max_meals = philo->table->times_each_philosopher_must_eat;
		philo[index].someone_died = false;
		philo[index].finish_eating = false;
		if (pthread_mutex_init(&philo[index].monitor_communication, NULL) != 0)
		{
			clean_mutexes_number_of_meals(philo, index);
			printf("Error: mutex init failed\n");
			return (false);
		}
		philo[index].left_fork = &forks[index];
		if (index == 0)
			philo[index].right_fork = &forks[number_of_philos - 1];
		else
			philo[index].right_fork = &forks[index - 1];
		index++;
	}
	return (true);
}

static void	assign_table_to_philo(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		table->philos[index].table = table;
		table->philos[index].last_meal_time = get_time_in_ms();
		index++;
	}
}

bool	philos_take_their_seats(t_table *table)
{
	assign_table_to_philo(table);
	if (!assign_data_to_philo(table->philos, table->number_of_philosophers,
		table->forks))
	{
		printf("Error: mutex init failed\n");
		return (false);
	}
	return (true);
}
