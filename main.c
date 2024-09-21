/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:05:21 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/20 20:11:32 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program		program;

	if (ac != 5 && ac != 6)
		write(2, "Invalid Num of Arguments\n", 25);
	parsing(av);
	init_program(&program, av);
	call_to_action(&program);
	destory_all(NULL, &program);
	return (0);
}
