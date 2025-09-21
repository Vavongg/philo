/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:46:13 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/20 16:15:31 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free
# include <unistd.h>    // write, usleep
# include <stdbool.h>
# include <pthread.h>   // mutex + threads
# include <sys/time.h>  // gettimeofday
# include <limits.h>    // INT_MAX

// Couleurs ANSI pour printf

# define RESET       "\033[0m"
# define BOLD        "\033[1m"

# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

typedef long long	t_msec;

//enum mutex && thread

typedef enum e_mutex_action
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
}	t_mutex_action;

typedef enum e_thread_action
{
	CREATE,
	JOIN,
	DETACH
}	t_thread_action;

typedef enum e_routine_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_routine_action;

// Structures

typedef struct s_philo
{
	int				id;
	int				meal_eaten;
	t_msec			last_meal;
	bool			full_meals;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				nb_philos;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				meals_required;
	t_msec			start_time;
	bool			simulation_active;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	*tab_forks;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}	t_table;

// err utils

void	print_error(const char *msg);

// Parsing

int		parse_input(t_table *table, char **av);

// Parsing utils

int		ft_isdigit(int c);
bool	ft_isspace(char c);
long	ft_atol(const char *str);

// functions utils

void	*safe_malloc(size_t bytes);
int		mutex_action(pthread_mutex_t *mutex, t_mutex_action mutex_op);
int		thread_action(pthread_t *thread, void *(*foo)(void *),
			void *data, t_thread_action thread_op);
void	ft_usleep(t_msec time_in_ms, t_table *table);

t_msec	actual_time(t_msec start_time);

// data init

int		data_init(t_table *table);

// simulation

void	solo_philo(t_table *table);
int		simulation_start(t_table *table);
void	*routine(void *data);
void	print_action(t_routine_action op, t_philo *philo);
void	print_die(t_routine_action op, t_philo	*philo);
void	think(t_philo *philo);

// monitoring

bool	is_simulation_active(t_table *table);
void	stop_simulation(t_table *table);
void	*monitor_meals(void *arg);
void	*monitor_die(void *arg);
bool	check_all_full(t_table *table);

// clean

void	clean_all(t_table *table);

#endif
