/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:03:05 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/07 14:26:46 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_philos
{
	int					eating;
	long long			last_meal;
	long long			start_time;
	long long			time_to_survive;
	int					num_times_to_eat;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_philos;
	int					dead_flag;
	int					no_print;
	int					*forks;
	int					id;
	int					pid;
	int					all_ate_flag;
	sem_t				*write_lock;
	sem_t				*death_lock;
	sem_t				*forks_lock;
	sem_t				*death_message_lock;
}					t_philos;

int			parsing_bonus(char **av);
int			ft_isdigit_bonus(int c);
int			ft_atoi_bonus(const char *str);
int			init_program_bonus(t_philos *philos, char **av);
long long	get_current_time_bonus(void);
void		call_to_action_bonus(t_philos *philos, int *pids);
size_t		ft_strlen_bonus(const char *s);
void		waiting_bonus(long long ms, t_philos *philos);
void		eat_bonus(t_philos *philos);
void		*routine_bonus(t_philos *philos, int *pids);
void		sleeping_bonus(t_philos *philos);
void		print_message_bonus(t_philos *philos, char *str, int id);
void		eating_process(t_philos *philos);
void		ability_to_eat_bonus(t_philos *philos);
void		exit_dining_bonus(t_philos *philos, int *pids);
void		check_death_main_bonus(t_philos *philos);
#endif