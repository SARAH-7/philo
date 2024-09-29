/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:05:21 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/29 22:27:37 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_program		program;
	int				num_of_philos;

	if (ac != 5 && ac != 6)
		return (write(2, "Invalid Num of Arguments\n", 25), 1);
	if (!parsing(av))
		return (1);
	num_of_philos = atoi(av[1]);
	if (num_of_philos <= 0)
		return (write(2, "Invalid Num of Philosophers\n", 28), 1);
	program.philos = malloc(sizeof(t_philo) * (num_of_philos + 1));
	program.forks_lock = malloc(sizeof(pthread_mutex_t) * (num_of_philos + 1));
	if (!program.philos || !program.forks_lock)
		return (write(2, "Memory Allocation Failed\n", 26), 1);
	init_program(&program, av);
	call_to_action(&program);
	free(program.philos);
	free(program.forks_lock);
	return (0);
}
