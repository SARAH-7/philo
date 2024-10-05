/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:05:21 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/05 18:23:45 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)s = 0;
		s = (char *)s + 1;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*r;

	if (size != 0 && count > UINT_MAX / size)
		return (NULL);
	r = malloc(count * size);
	if (r == NULL)
		return (NULL);
	ft_bzero(r, count * size);
	return (r);
}

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
	program.philos = ft_calloc((num_of_philos + 1), sizeof(t_philo));
	if (!program.philos)
		return (write(2, "Memory Allocation Failed\n", 26), 1);
	program.forks_lock = ft_calloc((num_of_philos + 1),
			sizeof(pthread_mutex_t));
	if (!program.forks_lock)
		return (write(2, "Memory Allocation Failed\n", 26)
			, free(program.philos), 1);
	init_program(&program, av);
	call_to_action(&program);
	free(program.philos);
	free(program.forks_lock);
	free(program.forks);
	return (0);
}
