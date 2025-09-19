/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:43:34 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/19 14:47:34 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdbool.h>

static void	launch_forks(t_philo *philo, pthread_mutex_t *forks, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->nb_philos;
	if (philo->id % 2)
	{
		philo->right_fork = &forks[pos];
		philo->left_fork = &forks[(pos + 1) % philo_nbr];
	}
	else
	{
		philo->right_fork = &forks[(pos + 1) % philo_nbr];
		philo->left_fork = &forks[pos];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->nb_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full_meals = false;
		philo->meal_eaten = 0;
		philo->table = table;
		launch_forks(philo, table->tab_forks, i);
	}
}

int	data_init(t_table *table)
{
	int				i;
	struct timeval	tmp;

	i = -1;
	table->simulation_active = true;
	table->philos = safe_malloc(sizeof(t_philo) * table->nb_philos);
	table->tab_forks = safe_malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (table->tab_forks == NULL || table->philos == NULL)
		return (1);
	while (++i < table->nb_philos)
		mutex_action(&table->tab_forks[i], INIT);
	philo_init(table);
	gettimeofday(&tmp, NULL);
	table->start_time = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
	return (0);
}
