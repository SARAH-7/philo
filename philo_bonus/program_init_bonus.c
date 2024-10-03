/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:15:18 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/03 21:29:32 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_philos *philos)
{
	sem_unlink("write lock");
	sem_unlink("death lock");
	sem_unlink("forks lock");
	sem_unlink("death message lock");
	philos->write_lock = sem_open("write lock", O_CREAT, 0644,
			1);
	philos->death_lock = sem_open("death lock", O_CREAT, 0644,
			1);
	philos->death_message_lock = sem_open("death lock", O_CREAT, 0644,
			1);
	philos->forks_lock = sem_open("forks lock", O_CREAT, 0644,
			philos->forks_num);
	if (philos->write_lock == SEM_FAILED || philos->death_lock == SEM_FAILED
		|| philos->forks_lock == SEM_FAILED
		|| philos->death_message_lock == SEM_FAILED)
		return (0);
	return (1);
}

void	init_philos(t_philos *philos, char **av)
{
	philos->time_to_survive = ft_atoi_bonus(av[2]);
	philos->time_to_eat = ft_atoi_bonus(av[3]);
	philos->time_to_sleep = ft_atoi_bonus(av[4]);
	if (av[5])
		philos->num_times_to_eat = ft_atoi_bonus(av[5]);
	else
		philos->num_times_to_eat = -1;
	philos->eating = 0;
	philos->forks_num = philos->num_of_philos / 2;
	if (philos->forks_num == 0)
		philos->forks_num = 1;
	philos->last_meal = 0;
}

void	init_program_bonus(t_philos *philos, char **av)
{
	int	i;

	philos->dead_flag = 0;
	philos->no_print = 0;
	philos->all_ate_flag = 2;
	philos->start_time = 0;
	init_philos(philos, av);
	i = 0;
	philos->forks = malloc(sizeof(int) * (philos->forks_num + 1));
	if (!philos->forks)
	{
		free(philos->pid);
		exit(1);
	}
	while (++i <= philos->forks_num)
	{
		philos->pid[i] = 1;
		philos->forks[i] = 0;
	}
	if (!init_semaphores(philos))
	{
		write(2, "Error creating semaphores\n", 26);
		free(philos->forks);
		free(philos->pid);
	}
}
