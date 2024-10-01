/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:12:56 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/03 14:57:32 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death_main_bonus(t_philos *philo)
{
	sem_wait(philo->death_lock);
	if (philo->dead_flag)
	{
		print_message_bonus(philo, "died", philo->id);
		philo->no_print = 1;
		sem_post(philo->death_lock);
		exit_dining_bonus(philo);
		exit(EXIT_FAILURE);
	}
	sem_post(philo->death_lock);
}

void	ability_to_eat_bonus(t_philos *philo)
{
	long long	time;

	if (get_current_time_bonus() - philo->start_time - philo->last_meal
		+ philo->time_to_eat > philo->time_to_survive)
	{
		time = get_current_time_bonus() - philo->start_time;
		waiting_bonus(philo->time_to_survive - time, philo);
		sem_wait(philo->death_lock);
		philo->dead_flag = 1;
		print_message_bonus(philo, "died", philo->id);
		philo->no_print = 1;
		sem_post(philo->death_lock);
		sem_post((philo->forks_lock));
		exit_dining_bonus(philo);
		exit(1);
	}
}

void	waiting_bonus(long long ms, t_philos *philo)
{
	long long		start;
	long long		end;

	start = get_current_time_bonus();
	end = start + ms;
	while ((get_current_time_bonus()) < end)
	{
		check_death_main_bonus(philo);
		usleep(100);
	}
}

void	sleeping_bonus(t_philos *philo)
{
	print_message_bonus(philo, "is sleeping", philo->id);
	waiting_bonus(philo->time_to_sleep, philo);
}
