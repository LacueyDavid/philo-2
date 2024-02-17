/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:35:14 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/17 02:40:55 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_arguments_validity(argc, argv))
		return (EXIT_FAILURE);
	if (!prepare_the_table(&table, argc, argv))
		return (EXIT_FAILURE);
	if (!start_the_dinner(&table))
		return (EXIT_FAILURE);
	clean_the_table(&table, table.number_of_philosophers);
	return (EXIT_SUCCESS);
}
