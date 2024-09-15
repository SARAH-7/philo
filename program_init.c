/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:15:18 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/15 02:53:05 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_program *program)
{
	int	i;

	i = program->num_of_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(program->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(program->write_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(program->meal_lock), NULL))
		return (1);
	return (0);
}

void	init_input(t_program *program, char **av)
{
	program->num_of_philos = ft_atoi(av[1]);
	program->time_to_survive = ft_atoi(av[2]);
	program->time_to_eat = ft_atoi(av[3]);
	program->time_to_sleep = ft_atoi(av[4]);
	program->all_ate_flag = 0;
	program->dead_flag = 0;
	if (av[5])
		program->num_times_to_eat = ft_atoi(av[5]);
	else
		program->num_times_to_eat = -1;
}

void	init_philos(t_program *program)
{
	int	i;

	i = program->num_of_philos;
	while (--i >= 0)
	{
		program->philos[i].id = i;
		program->philos[i].eating = 0;
		program->philos[i].l_fork = i;
		program->philos[i].r_fork = (i + 1) % program->num_of_philos;
		program->philos[i].last_meal = 0;
		program->philos[i].program = program;
	}
}

int	init_program(t_program *program, char **av)
{
	init_input(program, av);
	if (init_mutex(program))
		return (1);
	init_philos(program);
	return (0);
}
