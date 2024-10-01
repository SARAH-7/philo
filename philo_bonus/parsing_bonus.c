/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:56:22 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/30 19:56:27 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	nums_check(char **av)
{
	int	i;

	if (ft_atoi_bonus(av[1]) >= INT_MAX)
		return (write(2, "Invalid Num of Philos\n", 22), 0);
	i = 1;
	while (av[i])
	{
		if (ft_atoi_bonus(av[i]) <= 0 || ft_atoi_bonus(av[i]) >= INT_MAX)
			return (write(2, "Input Should Be Greater than 0\n", 31), 0);
		i++;
	}
	return (1);
}

int	parsing_bonus(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit_bonus(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (!nums_check(av))
		return (0);
	return (1);
}
