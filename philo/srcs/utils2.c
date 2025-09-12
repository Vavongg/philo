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

static void	handle_mutex_error(int status, t_mutex_action mutex_op)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (mutex_op == LOCK || mutex_op == UNLOCK))
		print_error("The value specified by mutex is invalid.");
	else if (status == EINVAL && mutex_op == INIT)
		print_error("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		print_error("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (status == EPERM)
		print_error("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
			print_error("The process cannot allocate enough memomy to create another mutex.");
	else if (status == EBUSY)
			print_error("Mutex is locked.");
}

void	safe_mutex_handle(pthread_mutex_t *mutex, t_mutex_action mutex_op)
{
	if (mutex_op == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), mutex_op);
	else if (mutex_op == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), mutex_op);
	else if (mutex_op == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), mutex_op);
	else if (mutex_op ==  DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), mutex_op);
	else
		print_error("Wrong input for mutex operation");
}

static void	handle_thread_error(int status, t_thread_action thread_op)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		print_error("No resources to create another thread");
	else if (status == EPERM)
		print_error("The caller does not have appropriate permisssion\n");
	else if (status == EINVAL && thread_op == CREATE)
		print_error("The value specified by attr is invalid.");
	else if (status == EINVAL && (thread_op == JOIN || thread_op == DETACH))
		print_error("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		print_error("No thread could be found corresponding to that"
			  "specified by given thread ID, thread.");
	else if (status == EDEADLK)
		print_error("A deadlock was detected or the value of"
			  "thread specifies the calling thread.");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_thread_action thread_op)
{
	if (thread_op == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), thread_op);
	else if (thread_op == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), thread_op);
	else if (thread_op == DETACH)
		handle_thread_error(pthread_detach(*thread), thread_op);
	else
		print_error("Wrong input for thread_handle :"
			  " use <CREATE> <JOIN> <DETACH>");
}
