/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:39:55 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/11 12:45:24 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	(void)av;
	if (ac != 5 && ac != 6)
	{
		print_error("Invalid number of arguments.\n"
			GREEN"Usage: ./philo nb_philos time_to_die"
			" time_to_eat time_to_sleep [nb_meals]");
		return (1);
	}
	else
	{
		if (parse_input(&table, av))
			return (1);
		if (data_init(&table))
			return (1);
		//if(simulation(&table))
		//	return (1)
		//clean_all(&table); //philo full | 1 philo die
	}
	return (0);
}
