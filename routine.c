/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:12:56 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/21 03:28:23 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(size_t ms)
{
	size_t	start;
	size_t	end;

	start = get_current_time();
	end = start + ms;
	while (get_current_time() < (long long)end)
		usleep(100);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	sleeping(t_program *program, t_philo *philo)
{
	print_message(program, "is sleeping", philo->id);
	waiting(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&(program->forks[philo->l_fork]));
	print_message(program, "has taken left fork", philo->id);
	pthread_mutex_lock(&(program->forks[philo->r_fork]));
	print_message(program, "has taken right fork", philo->id);
	print_message(program, "is eating", philo->id);
	waiting(philo->time_to_eat);
	philo->last_meal = get_current_time();
	(philo->eating)++;
	pthread_mutex_unlock(&(program->forks[philo->r_fork]));
	pthread_mutex_unlock(&(program->forks[philo->l_fork]));
}
