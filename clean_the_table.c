/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_the_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:38:28 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 02:39:16 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_the_table(t_table *table, size_t size_to_clean)
{
	size_t	index;

	index = 0;
	while (index < size_to_clean)
	{
		pthread_mutex_destroy(&table->philos[index].monitor_communication);
		pthread_mutex_destroy(&table->forks[index]);
		index++;
	}
}
