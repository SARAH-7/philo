/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_exec_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:49:02 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/07 14:08:19 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_repeat_count(t_philos *philo)
{
	int	repeat;

	if (philo->num_times_to_eat == -1)
		repeat = 2;
	else
		repeat = philo->num_times_to_eat + 1;
	return (repeat);
}

void	eat_bonus(t_philos *philo)
{
	check_death_main_bonus(philo);
	if (philo->num_of_philos == 1)
	{
		print_message_bonus(philo, "has taken the fork", philo->id);
		waiting_bonus(philo->time_to_survive, philo);
		sem_wait((philo->death_lock));
		philo->dead_flag = 1;
		sem_post((philo->death_lock));
		return ;
	}
	sem_wait((philo->forks_lock));
	sem_wait((philo->forks_lock));
	print_message_bonus(philo, "has taken the fork", philo->id);
	print_message_bonus(philo, "has taken the fork", philo->id);
	print_message_bonus(philo, "is eating", philo->id);
	ability_to_eat_bonus(philo);
	check_death_main_bonus(philo);
	philo->eating++;
	waiting_bonus(philo->time_to_eat, philo);
	philo->last_meal = get_current_time_bonus();
	sem_post(philo->forks_lock);
	sem_post(philo->forks_lock);
	check_death_main_bonus(philo);
}

void	*routine_bonus(t_philos *philo, int *pid)
{
	int			repeat;

	free(pid);
	repeat = get_repeat_count(philo);
	while (--repeat)
	{
		eat_bonus(philo);
		check_death_main_bonus(philo);
		sleeping_bonus(philo);
		check_death_main_bonus(philo);
		print_message_bonus(philo, "is thinking", philo->id);
		if (philo->num_times_to_eat == -1)
			repeat = 2;
		check_death_main_bonus(philo);
	}
	if (philo->num_times_to_eat != -1 && repeat == 0)
	{
		philo->all_ate_flag = 1;
		exit(0);
	}
	return (NULL);
}
