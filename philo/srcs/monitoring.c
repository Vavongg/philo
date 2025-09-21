/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:17:15 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/21 14:09:21 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	is_simulation_active(t_table *table)
{
	bool	active;

	mutex_action(&table->state_lock, LOCK);
	active = table->simulation_active;
	mutex_action(&table->state_lock, UNLOCK);
	return (active);
}

static bool	check_philos_life(t_table *table)
{
	int		i;
	t_msec	time_last_meal;

	i = 0;
	while (i < table->nb_philos)
	{
		mutex_action(&table->state_lock, LOCK);
		time_last_meal = actual_time(table->start_time)
			- table->philos[i].last_meal;
		mutex_action(&table->state_lock, UNLOCK);
		if (is_simulation_active(table)
			&& time_last_meal > table->time_to_die / 1000) //todo: enlever le / 1000
														   //ft_usleep()
		{
			print_die(DIE, &table->philos[i]);
			stop_simulation(table);
			return (true);
		}
		i++;
	}
	return (false);
}

void	*monitor_die(void *arg)
{
	t_table	*table;

	table = arg;
	while (is_simulation_active(table))
	{
		if (check_philos_life(table))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

bool	check_all_full(t_table *table)
{
	int		i;
	bool	all_full;
	int		meals_done;
	t_philo	*philo;

	i = 0;
	all_full = true;
	while (i < table->nb_philos)
	{
		philo = &table->philos[i];
		mutex_action(&table->state_lock, LOCK);
		meals_done = philo->meal_eaten;
		mutex_action(&table->state_lock, UNLOCK);
		if (meals_done < table->meals_required)
			all_full = false;
		i++;
	}
	return (all_full);
}

void	*monitor_meals(void *arg)
{
	t_table	*table;

	table = arg;
	if (table->meals_required <= 0)
		return (NULL);
	while (is_simulation_active(table))
	{
		if (check_all_full(table))
		{
			stop_simulation(table);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
