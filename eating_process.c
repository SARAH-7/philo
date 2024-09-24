/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 04:08:04 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/29 20:33:58 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	left_fork(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&(program->forks_lock[philo->l_fork]));
	if (program->forks[philo->l_fork] == 0 && program->num_of_philos != 1)
	{
		program->forks[philo->l_fork] = 1;
		print_message(program, "has taken the fork", philo->id);
	}
	else if (program->num_of_philos == 1)
	{
		print_message(program, "has taken the fork", philo->id);
		pthread_mutex_lock(&(program->death_lock));
		program->dead_flag = 1;
		pthread_mutex_unlock(&(program->death_lock));
	}
	else
		program->forks[philo->r_fork] = 0;
}

void	odd_philos(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&(program->forks_lock[philo->r_fork]));
	if (program->forks[philo->r_fork] == 0)
		program->forks[philo->r_fork] = 1;
	else
	{
		pthread_mutex_unlock(&(program->forks_lock[philo->r_fork]));
		return ;
	}
	left_fork(program, philo);
	print_message(program, "is eating", philo->id);
	if (!ability_to_eat(philo))
	{
		program->forks[philo->r_fork] = 0;
		pthread_mutex_unlock(&(program->forks_lock[philo->r_fork]));
		program->forks[philo->l_fork] = 0;
		pthread_mutex_unlock(&(program->forks_lock[philo->l_fork]));
	}
}

void	right_fork(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&(program->forks_lock[philo->r_fork]));
	if (program->forks[philo->r_fork] == 0 && program->num_of_philos != 1)
	{
		program->forks[philo->r_fork] = 1;
		print_message(program, "has taken the fork", philo->id);
	}
	else
		program->forks[philo->l_fork] = 0;
}

void	even_philos(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&(program->forks_lock[philo->l_fork]));
	if (program->forks[philo->l_fork] == 0 && program->num_of_philos != 1)
		program->forks[philo->l_fork] = 1;
	else
	{
		pthread_mutex_unlock(&(program->forks_lock[philo->l_fork]));
		return ;
	}
	right_fork(program, philo);
	print_message(program, "is eating", philo->id);
	if (!ability_to_eat(philo))
	{
		program->forks[philo->l_fork] = 0;
		pthread_mutex_unlock(&(program->forks_lock[philo->l_fork]));
		program->forks[philo->r_fork] = 0;
		pthread_mutex_unlock(&(program->forks_lock[philo->r_fork]));
	}
}
