/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:12:56 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/05 18:22:28 by sbakhit          ###   ########.fr       */
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
	print_message(program, philo, "is sleeping", philo->id);
	if (!waiting(philo->time_to_sleep, philo))
		return (0);
	return (1);
}

int	release_forks(t_program	*program, t_philo *philo)
{
	program->forks[philo->r_fork] = 0;
	pthread_mutex_unlock(&(program->forks_lock[philo->r_fork]));
	program->forks[philo->l_fork] = 0;
	pthread_mutex_unlock(&(program->forks_lock[philo->l_fork]));
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
	{
		if (program->num_of_philos != 1)
			release_forks(program, philo);
		return (print_message(philo->program, philo, "died", philo->id), 0);
	}
	philo->eating++;
	if (!waiting(philo->time_to_eat, philo))
		return (release_forks(program, philo), 0);
	philo->last_meal = get_current_time();
	release_forks(program, philo);
	return (1);
}
