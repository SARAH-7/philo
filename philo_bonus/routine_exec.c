/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:49:02 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/29 22:28:00 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_dining(t_program *program)
{
	int	i;

	i = 0;
	while (++i <= program->num_of_philos)
		pthread_mutex_destroy(&(program->forks_lock[i]));
	pthread_mutex_destroy(&(program->write_lock));
	pthread_mutex_destroy(&(program->death_lock));
	pthread_mutex_destroy(&(program->death_message_lock));
	pthread_mutex_destroy(&(program->all_ate_lock));
}

int	get_repeat_count(t_philo *philo)
{
	int	repeat;

	if (philo->num_times_to_eat == -1)
		repeat = 2;
	else
		repeat = philo->num_times_to_eat + 1;
	return (repeat);
}

int	execute_eating_sleeping(t_program *program, t_philo *philo)
{
	if (!eat(philo))
		return (0);
	if (!sleeping(program, philo))
		return (0);
	return (1);
}

void	*routine(void *pointer)
{
	t_program	*program;
	t_philo		*philo;
	int			repeat;

	philo = (t_philo *)pointer;
	program = philo->program;
	philo->start_time = get_current_time();
	repeat = get_repeat_count(philo);
	while (--repeat && !check_death_main(philo))
	{
		if (!execute_eating_sleeping(program, philo))
			return (NULL);
		print_message(program, "is thinking", philo->id);
		if (philo->num_times_to_eat == -1)
			repeat = 2;
	}
	pthread_mutex_lock(&(program->all_ate_lock));
	if (philo->num_times_to_eat != -1 && repeat == 0)
		program->all_ate_flag = 1;
	pthread_mutex_unlock(&(program->all_ate_lock));
	return (NULL);
}
