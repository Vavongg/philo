/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:21:02 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/20 13:26:22 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clean_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		mutex_action(&table->tab_forks[i], DESTROY);
		i++;
	}
    i = 0;
	mutex_action(&table->print_lock, DESTROY);
	mutex_action(&table->state_lock, DESTROY);
	free(table->tab_forks);
	free(table->philos);
}
