/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:39 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/29 20:23:36 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_program *program, t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= program->num_of_philos && !check_death_main(&philo[i]))
	{
		if (pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]))
			return (exit_dining(program), 1);
		// pthread_mutex_lock(&(program->death_lock));
		// if (program->dead_flag)
		// 	return (pthread_mutex_unlock(&(program->death_lock)), 1);
		// pthread_mutex_unlock(&(program->death_lock));
	}
	return (0);
}

void	wait_for_end(t_program *program)
{
	while (1)
	{
		pthread_mutex_lock(&(program->all_ate_lock));
		pthread_mutex_lock(&(program->death_lock));
		if (program->dead_flag || program->all_ate_flag)
			break ;
		pthread_mutex_unlock(&(program->death_lock));
		pthread_mutex_unlock(&(program->all_ate_lock));
		usleep(100);
	}
	pthread_mutex_unlock(&(program->death_lock));
	pthread_mutex_unlock(&(program->all_ate_lock));
}

int	join_threads(t_program *program, t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= program->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (exit_dining(program), 1);
	}
	return (0);
}

int	call_to_action(t_program *program)
{
	t_philo	*philo;

	philo = program->philos;
	program->start_time = get_current_time();
	if (create_threads(program, philo))
		return (1);
	wait_for_end(program);
	if (join_threads(program, philo))
		return (1);
	exit_dining(program);
	return (0);
}
