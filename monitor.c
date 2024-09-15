/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:10:02 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/15 03:33:29 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_program *program, char *str, int id)
{
	size_t	time;

	pthread_mutex_lock(&(program->write_lock));
	time = get_current_time() - program->start_time;
	if (!program->dead_flag)
		printf("%zums [id:%d] %s\n", time, id + 1, str);
	pthread_mutex_unlock(&(program->write_lock));
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
