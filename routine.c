/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:12:56 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/24 03:31:59 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mid_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->program->write_lock));
	if (get_current_time() - philo->start_time - philo->last_meal
		+ philo->time_to_eat > philo->time_to_survive)
	{
		philo->program->dead_flag = 1;
		philo->program->all_ate_flag = 0;
		pthread_mutex_unlock(&(philo->program->write_lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->program->write_lock));
	return (0);
}

void	waiting(size_t ms)
{
	size_t	start;
	size_t	end;

	start = get_current_time();
	end = start + ms;
	while ((get_current_time()) < (long long)end)
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

int	eat(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	if (philo->id % 2)
	{
		pthread_mutex_lock(&(program->forks_lock[philo->r_fork]));
		if (program->forks[philo->r_fork] == 0)
		{
			program->forks[philo->r_fork] = 1;
			print_message(program, "has taken right fork", philo->id);
		}
		else
			return (pthread_mutex_unlock(
					&(program->forks_lock[philo->r_fork])), 0);
		if (mid_death(philo))
		{
			program->forks[philo->r_fork] = 0;
			return (pthread_mutex_unlock(
					&(program->forks_lock[philo->r_fork])), 0);
		}
		pthread_mutex_lock(&(program->forks_lock[philo->l_fork]));
		if (program->forks[philo->l_fork] == 0 && program->num_of_philos != 1)
		{
			program->forks[philo->l_fork] = 1;
			print_message(program, "has taken left fork", philo->id);
		}
		else
		{
			program->forks[philo->r_fork] = 0;
			return (pthread_mutex_unlock(&(program->forks_lock[philo->l_fork])),
				pthread_mutex_unlock(&(program->forks_lock[philo->r_fork])), 0);
		}
	}
	else
	{
		pthread_mutex_lock(&(program->forks_lock[philo->l_fork]));
		if (program->forks[philo->l_fork] == 0)
		{
			program->forks[philo->l_fork] = 1;
			print_message(program, "has taken left fork", philo->id);
		}
		else
			return (pthread_mutex_unlock(
					&(program->forks_lock[philo->l_fork])), 0);
		if (mid_death(philo))
		{
			program->forks[philo->l_fork] = 1;
			return (pthread_mutex_unlock(
					&(program->forks_lock[philo->l_fork])),
				pthread_mutex_unlock(&(program->forks_lock[philo->r_fork])), 0);
		}
		pthread_mutex_lock(&(program->forks_lock[philo->r_fork]));
		if (program->forks[philo->r_fork] == 0 && program->num_of_philos != 1)
		{
			program->forks[philo->r_fork] = 1;
			print_message(program, "has taken right fork", philo->id);
		}
		else
		{
			program->forks[philo->l_fork] = 0;
			return (pthread_mutex_unlock(&(program->forks_lock[philo->r_fork])),
				pthread_mutex_unlock(&(program->forks_lock[philo->l_fork])), 0);
		}
	}
	print_message(program, "is eating", philo->id);
	philo->eating++;
	waiting(philo->time_to_eat);
	pthread_mutex_lock(&(philo->program->write_lock));
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&(philo->program->write_lock));
	program->forks[philo->r_fork] = 0;
	pthread_mutex_unlock(&(program->forks_lock[philo->r_fork]));
	program->forks[philo->l_fork] = 0;
	pthread_mutex_unlock(&(program->forks_lock[philo->l_fork]));
	return (1);
}
