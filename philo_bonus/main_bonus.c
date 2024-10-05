/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:05:21 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/03 10:27:12 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_philos	philos;
	int			*pids;

	if (ac != 5 && ac != 6)
		return (write(2, "Invalid Num of Arguments\n", 25), 1);
	if (!parsing_bonus(av))
		return (1);
	philos.num_of_philos = ft_atoi_bonus(av[1]);
	pids = malloc(sizeof(int) * (philos.num_of_philos + 1));
	if (!pids)
		return (1);
	if (!init_program_bonus(&philos, av))
		return (free(pids), 1);
	call_to_action_bonus(&philos, pids);
	return (0);
}
