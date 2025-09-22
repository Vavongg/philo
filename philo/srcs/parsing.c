/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:49:36 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/22 22:17:18 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	assign_time(t_msec *dest, const char *str)
{
	long	tmp;

	tmp = ft_atol(str);
	if (tmp == -1 || tmp > LONG_MAX)
		return (1);
	if (tmp < 60)
		return (print_error("timestamps <= 60ms"), 1);
	*dest = tmp;
	return (0);
}

int	parse_input(t_table *table, char **av)
{
	long	tmp;

	tmp = ft_atol(av[1]);
	if (tmp < 1 || tmp > 200)
		return (print_error("wrong number of philo"), 1);
	table->nb_philos = (int)tmp;
	if (assign_time(&table->time_to_die, av[2]))
		return (1);
	if (assign_time(&table->time_to_eat, av[3]))
		return (1);
	if (assign_time(&table->time_to_sleep, av[4]))
		return (1);
	if (av[5])
	{
		tmp = ft_atol(av[5]);
		if (tmp < 1)
			return (print_error("meals_required must be positive"), 1);
		table->meals_required = (int)tmp;
	}
	else
		table->meals_required = -1;
	return (0);
}
