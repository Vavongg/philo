/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:17:15 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/20 13:57:45 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool is_simulation_active(t_table *table)
{
    bool active;

    mutex_action(&table->state_lock, LOCK);
    active = table->simulation_active;
    mutex_action(&table->state_lock, UNLOCK);

    return (active);
}

void	stop_simulation(t_table *table)
{
	mutex_action(&table->state_lock, LOCK);
	table->simulation_active = false;
	mutex_action(&table->state_lock, UNLOCK);
}

void *monitor_die(void *arg)
{
    t_table *table = arg;
    int i;
    t_msec time_last_meal;

    while (is_simulation_active(table))
    {
        i = 0;
        
        while (i < table->nb_philos)
        {
            mutex_action(&table->state_lock, LOCK);
            time_last_meal = actual_time(table->start_time) - table->philos[i].last_meal;
            mutex_action(&table->state_lock, UNLOCK);
            if (is_simulation_active(table) && time_last_meal > table->time_to_die / 1000)
            {
                print_die(DIE, &table->philos[i]);
                stop_simulation(table);
                return NULL;
            }
            i++;
        }
        usleep(100);
    }
    return NULL;
}

bool check_all_full(t_table *table)
{
    int i = 0;
    bool all_full;
    int meals_done;
    t_philo *philo;

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
    return all_full;
}

void *monitor_meals(void *arg)
{
    t_table *table = (t_table *)arg;

    if (table->meals_required <= 0)
        return NULL;

    while (is_simulation_active(table))
    {
        if (check_all_full(table))
        {
            stop_simulation(table);
            return NULL;
        }
        usleep(100);
    }

    return NULL;
}


