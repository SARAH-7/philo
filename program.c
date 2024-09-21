/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:39 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/21 06:19:24 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_dining(t_program *program)
{
	int	i;

	i = 0;
	while (++i <= program->num_of_philos)
		pthread_mutex_destroy(&(program->forks_lock[i]));
	pthread_mutex_destroy(&(program->write_lock));
	pthread_mutex_destroy(&(program->eating_counter_lock));
}

int	end_program_checker(t_program *program, t_philo *philo)
{
	int			i;
	int			flag;

	flag = 1;
	i = 1;
	while (i <= program->num_of_philos)
	{
		if (philo[i].num_times_to_eat == -1)
		{
			if (philo[i].eating < 1)
			{
				flag = 0;
				break ;
			}
		}
		else
		{
			if (philo[i].eating < philo[i].num_times_to_eat)
			{
				flag = 0;
				break ;
			}
		}
	}
	return (flag);
}

void	*routine(void *pointer)
{
	t_program	*program;
	t_philo		*philo;
	int			repeat;

	philo = (t_philo *)pointer;
	program = philo->program;
	if (philo->num_times_to_eat == -1)
		repeat = 1;
	else
		repeat = philo->num_times_to_eat;
	if (philo->id % 2 == 0)
		usleep(150);
	while (repeat > 0 && !program->dead_flag)
	{
		eat(philo);
		pthread_mutex_lock(&(program->eating_counter_lock));
		program->eating_counter++;
		pthread_mutex_unlock(&(program->eating_counter_lock));
		pthread_mutex_lock(&(program->eating_counter_lock));
		if (program->eating_counter == program->num_of_philos)
		{
			pthread_mutex_unlock(&(program->eating_counter_lock));
			return (NULL);
		}
		pthread_mutex_unlock(&(program->eating_counter_lock));
		if (repeat > 0)
		{
			sleeping(program, philo);
			print_message(program, "is thinking", philo->id);
		}
		repeat--;
	}
	return (NULL);
}

void	death_checker(t_program *program, t_philo *philo, int flag)
{
	int			i;
	long long	time;

	i = 0;
	time = time_diff(philo[i].last_meal, get_current_time());
	while (++i <= program->num_of_philos && !program->dead_flag)
	{
		if (time >= program->philos[i].time_to_survive && !flag)
		{
			print_message(program, "died", philo[i].id);
			program->dead_flag = 1;
			return ;
		}
	}
}

int	call_to_action(t_program *program)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = program->philos;
	program->start_time = get_current_time();
	while (++i <= program->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]))
			return (exit_dining(program), 1);
	}
	i = 0;
	while (++i <= program->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (exit_dining(program), 1);
		pthread_mutex_lock(&(program->eating_counter_lock));
		if (program->eating_counter == program->num_of_philos)
		{
			pthread_mutex_unlock(&(program->eating_counter_lock));
			break ;
		}
		pthread_mutex_unlock(&(program->eating_counter_lock));
	}
	death_checker(program, program->philos,
		end_program_checker(program, program->philos));
	exit_dining(program);
	return (0);
}
