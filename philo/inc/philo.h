/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:46:13 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/03 20:41:36 by ainthana         ###   ########.fr       */
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
# include "../libft/libft.h"

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

typedef long long   t_msec; // millisecond timestamp

// Structures

typedef struct s_philo
{
    int             id;
    int             meal_eaten;
    t_msec          last_meal;
    bool            full_meals;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_table  *table;
}   t_philo;

typedef struct s_table
{
    int             nb_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_required;
    t_msec          start_time;
    bool            simulation_active;
    pthread_mutex_t state_lock;
    pthread_mutex_t *tab_forks;
    pthread_mutex_t print_lock;
    t_philo         *philos;
}   t_table;

// Srcs

void	print_error(const char *msg);
void	parse_input(t_table *table, char **av);
long	ft_atol(const char *str);

#endif

