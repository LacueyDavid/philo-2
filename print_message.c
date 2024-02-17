/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:36:41 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 02:19:22 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	size_t	time;

	time = get_time_in_ms() - philo->table->dinner_start_time;
	printf("%ld %ld %s\n", time, philo->id, message);
	return ;
}
