/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:03:05 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/11 17:59:16 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	int				num_of_philos;
	int				time_to_survive;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	int				id;
	int				eating;
	int				meals_eaten;
	int				start_time;
	int				last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	int				*dead;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	t_philo			*philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}					t_program;

int		parsing(char **av, t_philo	*philos);
char	ft_isdigit(int c);
int		ft_atoi(const char *str);
void	init_program(t_program *program, t_philo *philos,
			pthread_mutex_t *forks);
#endif