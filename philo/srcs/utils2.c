/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:07:07 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/12 12:26:07 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	mutex_action(pthread_mutex_t *mutex,
			t_mutex_action mutex_op)
{
	if (mutex_op == LOCK)
		pthread_mutex_lock(mutex);
	else if (mutex_op == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (mutex_op == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (mutex_op == DESTROY)
		pthread_mutex_destroy(mutex);
	else
	{
		print_error("Wrong input for mutex operation");
		return (1);
	}
	return (0);
}

int	thread_action(pthread_t *thread, void *(*foo)(void *),
		void *data, t_thread_action thread_op)
{
	if (thread_op == CREATE)
		pthread_create(thread, NULL, foo, data);
	else if (thread_op == JOIN)
		pthread_join(*thread, NULL);
	else
	{
		print_error("Wrong input for thread_handle :"
			" use <CREATE> <JOIN>");
		return (1);
	}
	return (0);
}
