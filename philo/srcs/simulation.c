/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:49:30 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/20 13:57:04 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	solo_philo(t_table *table)
{
	printf("0 1 has taken a fork\n");
	usleep(table->time_to_die);
	printf("%lld 1 died\n", actual_time(table->start_time));
}

static int	create_philos_and_monitors(t_table *table,
			pthread_t *monitor_die_thread,
			pthread_t *monitor_meals_thread)
{
	int	i;

	i = -1;
	while (++i < table->nb_philos)
	{
		if (thread_action(&table->philos[i].thread, routine,
				&table->philos[i], CREATE))
			return (1);
		if (mutex_action(&table->state_lock, LOCK))
			return (1);
		table->philos[i].last_meal = actual_time(table->start_time);
		if (mutex_action(&table->state_lock, UNLOCK))
			return (1);
	}
	if (thread_action(monitor_die_thread, monitor_die, table, CREATE))
		return (1);
	if (table->meals_required > 0)
	{
		if (thread_action(monitor_meals_thread, monitor_meals, table, CREATE))
			return (1);
	}
	return (0);
}

static int	join_philos_and_monitors(t_table *table,
			pthread_t monitor_die_thread,
			pthread_t monitor_meals_thread)
{
	int	i;

	i = -1;
	while (++i < table->nb_philos)
	{
		if (thread_action(&table->philos[i].thread, NULL,
				&table->philos[i], JOIN))
			return (1);
	}
	if (thread_action(&monitor_die_thread, NULL, table, JOIN))
		return (1);
	if (table->meals_required > 0)
	{
		if (thread_action(&monitor_meals_thread, NULL, table, JOIN))
			return (1);
	}
	return (0);
}

int	simulation_start(t_table *table)
{
	pthread_t	monitor_die_thread;
	pthread_t	monitor_meals_thread;

	if (table->nb_philos == 1)
	{
		solo_philo(table);
		return (0);
	}
	if (create_philos_and_monitors(table, &monitor_die_thread,
			&monitor_meals_thread))
		return (1);
	if (join_philos_and_monitors(table, monitor_die_thread,
			monitor_meals_thread))
		return (1);
	return (0);
}
