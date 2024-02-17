/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:36:09 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 08:36:34 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	simulation_finished(t_table *table, size_t exception)
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
		pthread_mutex_lock(&table->philos[index].monitor_communication);
		time = get_time_in_ms();
		if (table->philos[index].finish_eating == true)
			eat_finished++;
		else if (time - table->philos[index].last_meal_time
			> table->time_to_die)
		{
			print_message(&table->philos[index], "died");
			table->philos[index].someone_died = true;
			simulation_finished(table, index);
			pthread_mutex_unlock(&table->philos[index].monitor_communication);
			return (true);
		}
		pthread_mutex_unlock(&table->philos[index].monitor_communication);
		index++;
	}
	return (eat_finished == table->number_of_philosophers);
}

void	monitor(t_table *table)
{
	while (true)
	{
		if (check_simulation_finished(table))
			return ;
	}
	return ;
}
