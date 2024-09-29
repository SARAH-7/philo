/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:15:18 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/29 22:27:56 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_mutex(t_program *program)
{
	int	i;

	i = program->num_of_philos + 1;
	while (--i >= 1)
	{
		if (pthread_mutex_init(&(program->forks_lock[i]), NULL))
			return (0);
	}
	if (pthread_mutex_init(&(program->write_lock), NULL))
		return (0);
	if (pthread_mutex_init(&(program->death_lock), NULL))
		return (0);
	if (pthread_mutex_init(&(program->death_message_lock), NULL))
		return (0);
	if (pthread_mutex_init(&(program->all_ate_lock), NULL))
		return (0);
	return (1);
}

void	init_philos(t_program *program, char **av)
{
	int	i;

	i = 0;
	while (++i <= program->num_of_philos)
	{
		program->philos[i].time_to_survive = ft_atoi(av[2]);
		program->philos[i].time_to_eat = ft_atoi(av[3]);
		program->philos[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			program->philos[i].num_times_to_eat = ft_atoi(av[5]);
		else
			program->philos[i].num_times_to_eat = -1;
		program->philos[i].id = i;
		program->philos[i].eating = 0;
		program->philos[i].l_fork = i;
		program->philos[i].r_fork = (i % program->num_of_philos) + 1;
		program->philos[i].last_meal = 0;
		program->philos[i].program = program;
	}
}

void	init_program(t_program *program, char **av)
{
	int	i;

	program->num_of_philos = ft_atoi(av[1]);
	program->dead_flag = 0;
	program->eating_counter = 0;
	program->no_print = 0;
	program->all_ate_flag = 0;
	program->forks = malloc(sizeof(int) * (program->num_of_philos + 1));
	i = 0;
	while (++i <= program->num_of_philos)
		program->forks[i] = 0;
	init_philos(program, av);
	if (!init_mutex(program))
		write(2, "Error creating mutex\n", 21);
}
