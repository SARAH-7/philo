/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:39 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/15 05:49:00 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destory_all(char *str, t_program *program)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(program->forks);
}

void	exit_dining(t_program *program, t_philo	*philo)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL))
			destory_all("Thread creation error", program);
	}
	i = -1;
	while (++i < program->num_of_philos)
		pthread_mutex_destroy(&(program->forks[i]));
	pthread_mutex_destroy(&(program->write_lock));
}

void	*routine(void *pointer)
{
	t_program	*program;
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)pointer;
	program = philo->program;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!program->dead_flag)
	{
		eat(philo);
		if (program->all_ate_flag)
			break ;
		print_message(program, "is sleeping", philo->id);
		sleeping(program);
		print_message(program, "is thinking", philo->id);
		i++;
	}
	return (NULL);
}

void	death_checker(t_program *pro, t_philo	*ph)
{
	int	i;

	while (!(pro->all_ate_flag))
	{
		i = -1;
		while (++i < pro->num_of_philos && !(pro->dead_flag))
		{
			pthread_mutex_lock(&(pro->meal_lock));
			// printf("time_diff %d \n", get_current_time() - ph[i].last_meal);
			// printf("pro->time_to_survive %d \n", pro->time_to_survive);
			if (time_diff(ph[i].last_meal,
					get_current_time()) > pro->time_to_survive)
			{
				print_message(pro, "died", i);
				pro->dead_flag = 1;
			}
			pthread_mutex_unlock(&(pro->meal_lock));
			usleep(100);
		}
		if (pro->dead_flag)
			break ;
		i = 0;
		while (pro->num_times_to_eat != -1 && i < pro->num_of_philos
			&& ph[i].eating >= pro->num_times_to_eat)
			i++;
		if (i == pro->num_of_philos)
			pro->all_ate_flag = 1;
	}
}

int	call_to_action(t_program *program)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = program->philos;
	program->start_time = get_current_time();
	while (i < program->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]))
			return (destory_all("Thread creation error", program), 1);
		philo[i].last_meal = get_current_time();
		i++;
	}
	death_checker(program, program->philos);
	exit_dining(program, philo);
	return (0);
}
