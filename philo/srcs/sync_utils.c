/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:07:07 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/20 13:19:29 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	mutex_action(pthread_mutex_t *mutex, t_mutex_action mutex_op)
{
	int	status;

	if (mutex_op == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (mutex_op == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (mutex_op == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (mutex_op == DESTROY)
		status = pthread_mutex_destroy(mutex);
	else
	{
		print_error("Wrong input for mutex operation");
		return (1);
	}
	if (status != 0)
	{
		print_error("Mutex operation failed");
		return (1);
	}
	return (0);
}

int	thread_action(pthread_t *thread, void *(*foo)(void *),
		void *data, t_thread_action thread_op)
{
	int	status;

	if (thread_op == CREATE)
		status = pthread_create(thread, NULL, foo, data);
	else if (thread_op == JOIN)
		status = pthread_join(*thread, NULL);
	else
	{
		print_error("Wrong input for thread_handle: use <CREATE> <JOIN>");
		return (1);
	}
	if (status != 0)
	{
		print_error("Thread operation failed");
		return (1);
	}
	return (0);
}

t_msec	actual_time(t_msec start_time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000) - start_time);
}

// void	ft_usleep(t_msec time_in_us, t_table *table)
// {
// 	t_msec current_time;

// 	current_time = actual_time(table->start_time);
// 	while (actual_time(table->start_time) - current_time < time_in_us / 1000)
// 	{
// 		usleep(100);
// 		if (is_simulation_active(table))
// 			return ;
// 	}
		
// }