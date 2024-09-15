/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:05:21 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/15 05:46:39 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program		program;

	if (ac != 5 && ac != 6)
		return (printf("Invalid Num of Arguments"), 1);
	if (!parsing(av))
		return (1);
	if (init_program(&program, av))
		return (1);
	call_to_action(&program);
	destory_all(NULL, &program);
	return (0);
}
