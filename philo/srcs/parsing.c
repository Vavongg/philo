/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:49:36 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/03 20:31:30 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	parse_input(t_table *table, char **av)
{
	table->nb_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		print_error("timestamps >= 60ms");
	if (table->nb_philos < 1 || table->nb_philos > 200)
		print_error("wrong number of philo");
	if (av[5])
		table->meals_required = ft_atol(av[5]);
	else
		table->meals_required = -1;
}
