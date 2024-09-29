/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:10:02 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/29 22:27:50 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_program *program, char *message, int id)
{
	pthread_mutex_lock(&(program->death_message_lock));
	if (!program->no_print)
	{
		pthread_mutex_lock(&(program->write_lock));
		printf("%lldms [id:%d] %s\n", get_current_time()
			- program->start_time, id, message);
		pthread_mutex_unlock(&(program->write_lock));
	}
	pthread_mutex_unlock(&(program->death_message_lock));
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
