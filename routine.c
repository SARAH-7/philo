/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:12:56 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/26 23:12:47 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_main(t_philo *philo)
{
	pthread_mutex_lock(&(philo->program->death_lock));
	if (philo->program->dead_flag)
	{
		pthread_mutex_unlock(&(philo->program->death_lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->program->death_lock));
	return (0);
}

int	ability_to_eat(t_philo *philo)
{
	long long	time;

	if (check_death_main(philo))
		return (0);
	if (get_current_time() - philo->start_time - philo->last_meal
		+ philo->time_to_eat > philo->time_to_survive)
	{
		time = get_current_time() - philo->start_time;
		if (!waiting(philo->time_to_survive - time, philo))
			return (0);
		pthread_mutex_lock(&(philo->program->death_lock));
		philo->program->dead_flag = 1;
		print_message(philo->program, "died", philo->id);
		philo->program->no_print = 1;
		pthread_mutex_unlock(&(philo->program->death_lock));
		return (0);
	}
	return (1);
}

int	waiting(long long ms, t_philo *philo)
{
	long long		start;
	long long		end;

	start = get_current_time();
	end = start + ms;
	while ((get_current_time()) < end)
	{
		if (check_death_main(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

int	sleeping(t_program *program, t_philo *philo)
{
	print_message(program, "is sleeping", philo->id);
	if (!waiting(philo->time_to_sleep, philo))
		return (0);
	return (1);
}

int	eat(t_philo *philo)
{
	t_program	*program;

	if (check_death_main(philo))
		return (0);
	program = philo->program;
	if (philo->id % 2)
		odd_philos(program, philo);
	else
		even_philos(program, philo);
	if (check_death_main(philo))
		return (print_message(philo->program, "died", philo->id), 0);
	philo->eating++;
	if (!waiting(philo->time_to_eat, philo))
		return (0);
	philo->last_meal = get_current_time();
	program->forks[philo->r_fork] = 0;
	pthread_mutex_unlock(&(program->forks_lock[philo->r_fork]));
	program->forks[philo->l_fork] = 0;
	pthread_mutex_unlock(&(program->forks_lock[philo->l_fork]));
	return (1);
}
