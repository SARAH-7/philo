/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:42:08 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/29 22:27:52 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	nums_check(char **av)
{
	int	i;

	if (ft_atoi(av[1]) >= INT_MAX)
		return (write(2, "Invalid Num of Philos\n", 22), 0);
	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (write(2, "Input Should Be Greater than 0\n", 31), 0);
		i++;
	}
	return (1);
}

int	parsing(char **av)
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
	if (!nums_check(av))
		return (0);
	return (1);
}
