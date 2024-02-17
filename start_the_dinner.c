/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_dinner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:50:38 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 04:48:12 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulation_finished(t_table *table, size_t exception)
{
	size_t	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (index == exception)
		{
			index++;
			continue ;
		}
		pthread_mutex_lock(&table->philos[index].monitor_communication);
		table->philos[index].someone_died = true;
		pthread_mutex_unlock(&table->philos[index].monitor_communication);
		index++;
	}
}

static bool	check_simulation_finished(t_table *table)
{
	size_t	index;
	size_t	eat_finished;
	size_t	time;

	index = 0;
	eat_finished = 0;
	while (index < table->number_of_philosophers)
	{
		time = get_time_in_ms();
		pthread_mutex_lock(&table->philos[index].monitor_communication);
		if (table->philos[index].finish_eating == true)
			eat_finished++;
		else if (time - table->philos[index].last_meal_time > table->time_to_die)
		{
			printf("%zu %ld died\n", time - table->dinner_start_time, table->philos[index].id);
			table->philos[index].someone_died = true;
			simulation_finished(table, index);
			pthread_mutex_unlock(&table->philos[index].monitor_communication);
			return true;
		}
		pthread_mutex_unlock(&table->philos[index].monitor_communication);
		index++;
	}
	return (eat_finished == table->number_of_philosophers);
}

static void monitor(t_table *table)
{
	while(true)
	{
		if (check_simulation_finished(table))
			return ;
	}
	return ;
}

static bool	philosophers_start_their_routine(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_create(&table->philos[index].thread, NULL,
						   &philosophers_routine, &table->philos[index]) != 0)
		{
			clean_the_table(table, table->number_of_philosophers);
			return (false);
		}
		index++;
	}
	return (true);
}

static bool	wait_philosophers_finish_their_dinner(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_join(table->philos[index].thread, NULL) != 0)
		{
			printf("Error: pthread_join() failed\n");
			clean_the_table(table, table->number_of_philosophers);
			return (false);
		}
		index++;
	}
	return (true);
}

bool	start_the_dinner(t_table *table)
{
	if (table->number_of_philosophers == 1)
	{
		ft_usleep(table->time_to_die);
		print_message(&table->philos[0], "died.");
		return (true);
	}
	if (!philosophers_start_their_routine(table))
		return (false);
	monitor(table);
	if (!wait_philosophers_finish_their_dinner(table))
		return (false);
	return (true);
}
