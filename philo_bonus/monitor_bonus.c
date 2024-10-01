/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:10:02 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/03 14:26:27 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message_bonus(t_philos *philo, char *message, int id)
{
	sem_wait(philo->write_lock);
	if (!philo->no_print)
		printf("%lldms [id:%d] %s\n", get_current_time_bonus()
			- philo->start_time, id, message);
	sem_post(philo->write_lock);
}

long long	get_current_time_bonus(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
