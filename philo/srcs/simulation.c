/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:07:43 by tmalkawi          #+#    #+#             */
/*   Updated: 2025/09/18 18:07:43 by tmalkawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	solo_philo(t_table *table)
{
	printf("0 1 has taken a fork");
	usleep(table->time_to_die);
	printf("%d 1 died", table->time_to_die);
}

int	simulation_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nb_philos == 1)
		solo_philo(table);
	else
	{
		while (++i < table->nb_philos)
		{
			if (thread_action(&table->philos[i].thread, routine,
					&table->philos[i], CREATE))
				return (1);
		}
		i = -1;
		while (++i < table->nb_philos)
		{
			if (thread_action(&table->philos[i].thread, routine,
					&table->philos[i], JOIN))
				return (1);
		}
	}
	return (0);
}
