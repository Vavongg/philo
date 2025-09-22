/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:49:15 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/22 22:08:35 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	think(t_philo *philo)
{
	long long	time_to_think;

	if (is_simulation_active(philo->table) == false)
		return ;
	print_action(THINK, philo);
	if (philo->table->nb_philos % 2 == 1)
		time_to_think = (philo->table->time_to_eat * 2
				- philo->table->time_to_sleep);
	else
		time_to_think = philo->table->time_to_eat
			- philo->table->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 1;
	usleep(time_to_think);
}

void	print_action(t_routine_action op, t_philo *philo)
{
	mutex_action(&philo->table->state_lock, LOCK);
	if (philo->table->simulation_active)
	{
		mutex_action(&philo->table->print_lock, LOCK);
		if (op == FORK)
			printf("%lld %d has taken a fork\n",
				actual_time(philo->table->start_time), philo->id);
		else if (op == EAT)
			printf("%lld %d is eating\n",
				actual_time(philo->table->start_time), philo->id);
		else if (op == SLEEP)
			printf("%lld %d is sleeping\n",
				actual_time(philo->table->start_time), philo->id);
		else if (op == THINK)
			printf("%lld %d is thinking\n",
				actual_time(philo->table->start_time), philo->id);
		mutex_action(&philo->table->print_lock, UNLOCK);
	}
	mutex_action(&philo->table->state_lock, UNLOCK);
}

void	print_die(t_routine_action op, t_philo	*philo)
{
	mutex_action(&philo->table->print_lock, LOCK);
	if (op == DIE)
	{
		printf("%lld %d died\n",
			actual_time(philo->table->start_time), philo->id);
	}
	mutex_action(&philo->table->print_lock, UNLOCK);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	while (is_simulation_active(philo->table))
	{
		mutex_action(philo->right_fork, LOCK);
		print_action(FORK, philo);
		mutex_action(philo->left_fork, LOCK);
		print_action(FORK, philo);
		print_action(EAT, philo);
		mutex_action(&philo->table->state_lock, LOCK);
		philo->last_meal = actual_time(philo->table->start_time);
		philo->meal_eaten++;
		if (philo->meal_eaten == philo->table->meals_required)
			philo->full_meals = true;
		mutex_action(&philo->table->state_lock, UNLOCK);
		ft_usleep(philo->table->time_to_eat, philo->table);
		mutex_action(philo->right_fork, UNLOCK);
		mutex_action(philo->left_fork, UNLOCK);
		print_action(SLEEP, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
	return (NULL);
}
