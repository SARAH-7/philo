/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:03:05 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/15 04:20:32 by sbakhit          ###   ########.fr       */
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
	int					last_meal;
	struct s_program	*program;
	pthread_t			thread;
	int					r_fork;
	int					l_fork;
	int					*dead;
}					t_philo;

typedef struct s_program
{
	int				num_of_philos;
	int				time_to_survive;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	int				all_ate_flag;
	int				dead_flag;
	int				start_time;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks[PHILO_MAX];

}					t_program;

int			parsing(char **av);
char		ft_isdigit(int c);
int			ft_atoi(const char *str);
int			init_program(t_program *program, char **av);
int			get_current_time(void);
long long	time_diff(long long past, long long pres);
int			call_to_action(t_program *program);
size_t		ft_strlen(const char *s);
void		*monitor(void *pointer);
int			waiting(size_t milliseconds);
void		eat(t_philo *philo);
void		sleeping(t_program *program);
void		think(t_philo *philo);
void		print_message(t_program *program, char *str, int id);
int			dead_loop(t_philo *philo);
void		destory_all(char *str, t_program *program);
#endif