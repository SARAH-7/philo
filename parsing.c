/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:42:08 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/20 20:14:41 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if (i == 1 && ft_atoi(av[i]) <= 1)
// 	return (printf("0ms [id:1] has taken a fork\n0ms [id:1] died\n"), 0);
void	nums_check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			write(2, "Input Should Be Greater than 0\n", 31);
		i++;
	}
}

void	parsing(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			ft_isdigit(av[i][j]);
			j++;
		}
		i++;
	}
	nums_check(av);
}
