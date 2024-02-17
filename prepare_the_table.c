/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_the_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:30:06 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 02:43:14 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	table_take_the_timers(t_table *table, int argc, char **argv)
{
	table->dinner_start_time = get_time_in_ms();
	table->number_of_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		table->times_each_philosopher_must_eat = -1;
}

static bool	put_the_forks_on_the_table(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[index], NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			clean_the_table(table, index);
			return (false);
		}
		index++;
	}
	return (true);
}

bool	prepare_the_table(t_table *table, int argc, char **argv)
{
	table_take_the_timers(table, argc, argv);
	if (!put_the_forks_on_the_table(table))
		return (false);
	if (!philos_take_their_seats(table))
	{
		clean_the_table(table, table->number_of_philosophers);
		return (false);
	}
	return (true);
}
