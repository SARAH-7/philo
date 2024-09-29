/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:03:05 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/29 22:26:54 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					eating;
	int					meals_eaten;
	long long			last_meal;
	struct s_program	*program;
	pthread_t			thread;
	int					r_fork;
	int					l_fork;
	int					*dead;
	long long			start_time;
	long long			time_to_survive;
	int					num_times_to_eat;
	int					time_to_eat;
	int					time_to_sleep;
}					t_philo;

typedef struct s_program
{
	int				num_of_philos;
	int				time_to_sleep;
	int				dead_flag;
	int				no_print;
	long long		start_time;
	int				eating_counter;
	int				*forks;
	int				all_ate_flag;
	t_philo			*philos;
	pthread_mutex_t	all_ate_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	death_message_lock;
	pthread_mutex_t	*forks_lock;
}					t_program;

int			parsing(char **av);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		init_program(t_program *program, char **av);
long long	get_current_time(void);
int			call_to_action(t_program *program);
size_t		ft_strlen(const char *s);
void		*monitor(void *pointer);
int			waiting(long long ms, t_philo *philo);
int			eat(t_philo *philo);
int			sleeping(t_program *program, t_philo *philo);
void		think(t_philo *philo);
void		print_message(t_program *program, char *str, int id);
int			dead_loop(t_philo *philo);
void		even_philos(t_program *program, t_philo *philo);
void		odd_philos(t_program *program, t_philo *philo);
int			ability_to_eat(t_philo *philo);
void		exit_dining(t_program *program);
int			check_death_main(t_philo *philo);
void		*routine(void *pointer);
#endif