/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:42:08 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/15 05:28:56 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nums_check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (i == 1 && ft_atoi(av[i]) <= 1)
			return (printf("0ms [id:1] died\n"), 0);
		if (ft_atoi(av[i]) <= 0)
			return (printf("Input Should Be Greater than 0\n"), 0);
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
