/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_simulation_over.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:31:46 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 08:32:43 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_over(t_philo *philo, ssize_t count)
{
	if (philo->table->times_each_philosopher_must_eat != -1)
		if (count >= philo->table->times_each_philosopher_must_eat)
			return (true);
	pthread_mutex_lock(&philo->monitor_communication);
	if (philo->someone_died == true)
	{
		pthread_mutex_unlock(&philo->monitor_communication);
		return (true);
	}
	pthread_mutex_unlock(&philo->monitor_communication);
	return (false);
}
