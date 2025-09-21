/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:49:36 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/21 14:10:49 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*int	parse_input(t_table *table, char **av)
{
	table->nb_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
	{
		print_error("timestamps <= 60ms");
		return (1);
	}
	if (table->nb_philos < 1 || table->nb_philos > 200)
	{
		print_error("wrong number of philo");
		return (1);
	}
	if (av[5])
	{
		table->meals_required = ft_atol(av[5]);
		if (table->meals_required < 1)
			return (print_error("meals_required must be positive"), 1);
	}
	else
		table->meals_required = -1;
	return (0);
}*/

static int	assign_time(t_msec *dest, const char *str, const char *name)
{
	long	tmp;

	tmp = ft_atol(str);
	if (tmp == -1 || tmp > LONG_MAX / 1000)
		return (print_error(name), 1);
	if (tmp < 60)
		return (print_error("timestamps <= 60ms"), 1);
	*dest = tmp * 1000;
	return (0);
}

int	parse_input(t_table *table, char **av)
{
	long	tmp;

	tmp = ft_atol(av[1]);
	if (tmp < 1 || tmp > 200)
		return (print_error("wrong number of philo"), 1);
	table->nb_philos = (int)tmp;
	if (assign_time(&table->time_to_die, av[2],
			"time_to_die too large"))
		return (1);
	if (assign_time(&table->time_to_eat, av[3],
			"time_to_eat too large"))
		return (1);
	if (assign_time(&table->time_to_sleep, av[4],
			"time_to_sleep too large"))
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
