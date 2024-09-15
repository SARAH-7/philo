/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:12:56 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/15 04:15:33 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	waiting(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(ms / 10);
	return (0);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	sleeping(t_program	*program)
{
	long long	i;

	i = get_current_time();
	while (!(program->dead_flag))
	{
		if (time_diff(i, get_current_time()) >= program->time_to_sleep)
			break ;
		usleep(50);
	}
}

void	eat(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&(program->forks[philo->l_fork]));
	print_message(program, "has taken a fork", philo->id);
	pthread_mutex_lock(&(program->forks[philo->r_fork]));
	print_message(program, "has taken a fork", philo->id);
	pthread_mutex_lock(&(program->meal_lock));
	print_message(program, "is eating", philo->id);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&(program->meal_lock));
	sleeping(program);
	(philo->eating)++;
	pthread_mutex_unlock(&(program->forks[philo->l_fork]));
	pthread_mutex_unlock(&(program->forks[philo->r_fork]));
}
