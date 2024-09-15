/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:04 by sbakhit           #+#    #+#             */
/*   Updated: 2024/09/12 17:33:23 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	check_for_overflow(long long result, int sign, char a)
{
	if (sign == 1)
	{
		if ((result == LLONG_MAX / 10 && a > '7') || result > LLONG_MAX / 10)
			return (-1);
	}
	else if (sign == -1)
	{
		if ((result == LLONG_MAX / 10 && a > '8') || result > LLONG_MAX / 10)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;
	int		of;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		of = check_for_overflow(result, sign, *str);
		if (of != 1)
			return (of);
		result = result * 10 + *str - '0';
		str++;
	}
	return ((result * sign));
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
