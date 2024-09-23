/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:39 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/24 03:28:35 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_dining(t_program *program)
{
	int	i;

	i = 0;
	while (++i <= program->num_of_philos)
		pthread_mutex_destroy(&(program->forks_lock[i]));
	pthread_mutex_destroy(&(program->write_lock));
}

void	end_program_checker(t_program *program, t_philo *philo)
{
	int			i;

	i = 0;
	while (++i <= program->num_of_philos)
	{
		if (philo[i].num_times_to_eat == -1)
		{
			if (philo[i].eating < 1)
			{
				print_message(program, "died", philo[i].id);
				break ;
			}
		}
		else
		{
			if (philo[i].eating < philo[i].num_times_to_eat)
			{
				print_message(program, "died", philo[i].id);
				break ;
			}
		}
	}
}

void	*routine(void *pointer)
{
	t_program	*program;
	t_philo		*philo;
	int			repeat;
	long long	current_time;
	long long	time_remaining;

	philo = (t_philo *)pointer;
	program = philo->program;
	philo->start_time = get_current_time();
	if (philo->num_times_to_eat == -1)
		repeat = 2;
	else
		repeat = philo->num_times_to_eat + 1;
	while (--repeat && !program->dead_flag)
	{
		if (!eat(philo) || program->dead_flag)
		{
			program->dead_flag = 1;
			waiting(philo->time_to_survive);
			print_message(program, "died", philo->id);
			return (NULL);
		}
		pthread_mutex_lock(&(program->write_lock));
		current_time = get_current_time() - philo->start_time;
		time_remaining = philo->time_to_survive
			- (get_current_time() - philo->last_meal);
		if (time_remaining < philo->time_to_sleep)
		{
			program->dead_flag = 1;
			print_message(program, "died", philo->id);
			pthread_mutex_unlock(&(program->write_lock));
			return (NULL);
		}
		pthread_mutex_unlock(&(program->write_lock));
		sleeping(program, philo);
		print_message(program, "is thinking", philo->id);
		if (philo->num_times_to_eat == -1)
			repeat = 2;
	}
	return (NULL);
}

int	call_to_action(t_program *program)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = program->philos;
	program->start_time = get_current_time();
	while (++i <= program->num_of_philos && !program->dead_flag)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]))
			return (exit_dining(program), 1);
	}
	i = 0;
	while (++i <= program->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (exit_dining(program), 1);
	}
	exit_dining(program);
	return (0);
}
