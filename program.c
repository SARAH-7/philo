/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:39 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/22 09:29:43 by sbakhit          ###   ########.fr       */
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
}

int	end_program_checker(t_program *program, t_philo *philo)
{
	int			i;
	int			flag;

	flag = 1;
	i = 0;
	while (++i <= program->num_of_philos)
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
	long long	current_time;
	long long	time_remaining;

	philo = (t_philo *)pointer;
	program = philo->program;
	philo->last_meal = get_current_time() - philo->start_time;
	if (philo->num_times_to_eat == -1)
		repeat = 2;
	else
		repeat = philo->num_times_to_eat + 1;
	while (--repeat && !program->dead_flag)
	{
		pthread_mutex_lock(&(program->write_lock));
		current_time = get_current_time() - philo->start_time;
		time_remaining = philo->time_to_survive
			- time_diff(philo->last_meal, current_time);
		printf("\n\nid %d\n", philo->id);
		printf("gct %lld\n", get_current_time());
		printf("pst %lld\n", philo->start_time);
		printf("c %lld\n", current_time);
		printf("t %lld\n", time_remaining);
		printf("l %lld\n\n", philo->last_meal);
		if (time_remaining < philo->time_to_eat)
		{
			program->dead_flag = 1;
			pthread_mutex_unlock(&(program->write_lock));
			return (NULL);
		}
		pthread_mutex_unlock(&(program->write_lock));
		if (!eat(philo))
			return (usleep(philo->time_to_survive * 1000), NULL);
		philo->last_meal = get_current_time() - philo->start_time;
		sleeping(program, philo);
		print_message(program, "is thinking", philo->id);
		if (philo->num_times_to_eat == -1)
			repeat = 2;
	}
	return (NULL);
}
// void	*routine(void *pointer)
// {
// 	t_program	*program;
// 	t_philo		*philo;
// 	int			repeat;
// 	long long	start_time;

// 	philo = (t_philo *)pointer;
// 	program = philo->program;
// 	if (philo->num_times_to_eat == -1)
// 		repeat = 1;
// 	else
// 		repeat = philo->num_times_to_eat;

// 	// Stagger even-numbered philosophers by delaying their start
// 	if (philo->id % 2 == 0)
// 	{
// 		start_time = get_current_time();
// 		while (get_current_time() < start_time + 200) // Wait 200ms precisely
// 			usleep(100); // Sleep in short intervals to avoid busy waiting
// 	}

// 	while (repeat > 0 && !program->dead_flag)
// 	{
// 		if (!eat(philo))
// 			return (NULL);
// 		if (program->eating_counter < program->num_of_philos)
// 		{
// 			sleeping(program, philo);
// 			print_message(program, "is thinking", philo->id);
// 		}
// 		repeat--;
// 		if (philo->num_times_to_eat == -1)
// 			repeat = 1;
// 	}
// 	return (NULL);
// }

void	death_checker(t_program *program, t_philo *philo, int flag)
{
	int			i;
	long long	time;

	for (i = 0; i < program->num_of_philos; i++)
	{
		time = time_diff(philo[i].last_meal, get_current_time() - philo->start_time);
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
	}
	death_checker(program, program->philos,
		end_program_checker(program, program->philos));
	exit_dining(program);
	return (0);
}
