/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:36:39 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/22 03:10:30 by sbakhit          ###   ########.fr       */
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
	// long long	start_time;

	philo = (t_philo *)pointer;
	program = ((t_philo *)pointer)->program;
	if (philo->num_times_to_eat == -1)
		repeat = 2;
	else
		repeat = philo->num_times_to_eat + 1;
// Remove this part entirely or reduce it significantly
if (philo->id % 2 == 0) {
    long long start_time = get_current_time();
    long long delay = 100; // You can tweak this further
    while (get_current_time() < start_time + delay) {
        usleep(50);
    }

}

	while (--repeat && !program->dead_flag)
	{
		if (!eat(philo))
			return (NULL);
		sleeping(program, philo);
		print_message(program, "is thinking", philo->id);
		if (philo->num_times_to_eat == -1)
			repeat = 2;
	}
	return (NULL);
}

void	death_checker(t_program *program, t_philo *philo, int flag)
{
	int			i;
	long long	time;

	i = 0;
	while (++i <= program->num_of_philos && !program->dead_flag)
	{
		time = time_diff(philo[i].last_meal, get_current_time());
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
		if ((program->eating_counter == program->num_of_philos)
			|| philo->num_times_to_eat == program->eating_counter
			/ program->num_of_philos)
			break ;
	}
	death_checker(program, program->philos,
		end_program_checker(program, program->philos));
	exit_dining(program);
	return (0);
}
