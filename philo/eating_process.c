/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 04:08:04 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/05 18:22:33 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ability_to_eat(t_philo *philo)
{
	long long	time;

	if (check_death_main(philo))
		return ;
	if (get_current_time() - philo->start_time - philo->last_meal
		+ philo->time_to_eat > philo->time_to_survive)
	{
		time = get_current_time() - philo->start_time;
		if (!waiting(philo->time_to_survive - time, philo))
			return ;
		pthread_mutex_lock(&(philo->program->death_lock));
		philo->program->dead_flag = 1;
		print_message(philo->program, philo, "died", philo->id);
		pthread_mutex_lock(&(philo->program->death_message_lock));
		philo->program->no_print = 1;
		pthread_mutex_unlock(&(philo->program->death_message_lock));
		pthread_mutex_unlock(&(philo->program->death_lock));
	}
}

void	left_fork(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&(program->forks_lock[philo->l_fork]));
	if (program->forks[philo->l_fork] == 0 && program->num_of_philos != 1)
	{
		program->forks[philo->l_fork] = 1;
		print_message(program, philo, "has taken the fork", philo->id);
	}
	else
		program->forks[philo->r_fork] = 0;
}

void	odd_philos(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&(program->forks_lock[philo->r_fork]));
	if (program->forks[philo->r_fork] == 0 && program->num_of_philos != 1)
	{
		program->forks[philo->r_fork] = 1;
		print_message(program, philo, "has taken the fork", philo->id);
	}
	else
	{
		if (program->num_of_philos == 1)
		{
			waiting(philo->time_to_survive, philo);
			pthread_mutex_lock(&(program->death_lock));
			program->dead_flag = 1;
			pthread_mutex_unlock(&(program->death_lock));
		}
		pthread_mutex_unlock(&(program->forks_lock[philo->r_fork]));
		return ;
	}
	left_fork(program, philo);
	print_message(program, philo, "is eating", philo->id);
	ability_to_eat(philo);
}

void	right_fork(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&(program->forks_lock[philo->r_fork]));
	if (program->forks[philo->r_fork] == 0 && program->num_of_philos != 1)
	{
		program->forks[philo->r_fork] = 1;
		print_message(program, philo, "has taken the fork", philo->id);
	}
	else
		program->forks[philo->l_fork] = 0;
}

void	even_philos(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&(program->forks_lock[philo->l_fork]));
	if (program->forks[philo->l_fork] == 0 && program->num_of_philos != 1)
	{
		program->forks[philo->l_fork] = 1;
		print_message(program, philo, "has taken the fork", philo->id);
	}
	else
	{
		pthread_mutex_unlock(&(program->forks_lock[philo->l_fork]));
		return ;
	}
	right_fork(program, philo);
	print_message(program, philo, "is eating", philo->id);
	ability_to_eat(philo);
}
