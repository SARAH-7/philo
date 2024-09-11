/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:42:08 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/11 17:56:02 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nums_check(char **av, t_philo	*philos)
{
	int	i;

	if (ft_atoi(av[1]) <= 1)
		return (printf("Two or More Philos Are Needed\n"), 0);
	i = 2;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (printf("Input Should Be Greater than 0\n"), 0);
		i++;
	}
	return (1);
}

int	parsing(char **av, t_philo	*philos)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (!nums_check(av, philos))
		return (0);
	return (1);
}
