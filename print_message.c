/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:36:41 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 06:23:28 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->print);
	time = get_time_in_ms() - philo->table->dinner_start_time;
	printf("%ld %ld %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->table->print);
	return ;
}
