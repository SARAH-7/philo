/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:03:05 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/21 05:44:47 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_MAX 200

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
	long long			time_to_survive;
	int					num_times_to_eat;
	int					time_to_eat;
	int					time_to_sleep;
}					t_philo;

	// int				*forks;
typedef struct s_program
{
	int				num_of_philos;
	int				time_to_sleep;
	int				dead_flag;
	long long		start_time;
	int				eating_counter;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	eating_counter_lock;
	pthread_mutex_t	forks_lock[PHILO_MAX];

}					t_program;

void		parsing(char **av);
void		ft_isdigit(int c);
int			ft_atoi(const char *str);
void		init_program(t_program *program, char **av);
long long	get_current_time(void);
long long	time_diff(long long past, long long pres);
int			call_to_action(t_program *program);
size_t		ft_strlen(const char *s);
void		*monitor(void *pointer);
void		waiting(size_t milliseconds);
void		eat(t_philo *philo);
void		sleeping(t_program *program, t_philo *philo);
void		think(t_philo *philo);
void		print_message(t_program *program, char *str, int id);
int			dead_loop(t_philo *philo);
#endif