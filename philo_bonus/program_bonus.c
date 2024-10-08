/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:39 by sbakhit           #+#    #+#             */
/*   Updated: 2024/10/03 21:30:03 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_dining_bonus(t_philos *philo, int *pid)
{
	int	i;

	i = 0;
	while (++i <= philo->num_of_philos)
		kill(pid[i], SIGTERM);
	sem_close(philo->write_lock);
	sem_close(philo->death_lock);
	sem_close(philo->death_message_lock);
	sem_close(philo->forks_lock);
	sem_unlink("write lock");
	sem_unlink("death lock");
	sem_unlink("forks lock");
	sem_unlink("death message lock");
	free(pid);
	exit(EXIT_SUCCESS);
}

void	call_to_action_bonus(t_philos *philo, int *pids)
{
	int	i;
	int	status;

	philo->start_time = get_current_time_bonus();
	i = 0;
	while (++i <= philo->num_of_philos)
	{
		philo->id = i;
		philo->pid = fork();
		pids[i] = philo->pid;
		if (philo->pid < 0)
			exit_dining_bonus(philo, pids);
		if (philo->pid == 0)
		{
			routine_bonus(philo, pids);
			exit(0);
		}
		if (philo->all_ate_flag == 1)
			exit(0);
	}
	while (waitpid(-1, &status, 0) > 0)
		if (status > 0)
			exit_dining_bonus(philo, pids);
}
