/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:56:15 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/13 14:58:25 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_checker(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (!is_digit(av[i][j]))
				return (0);
		}
		if (ft_atoi(av[i]) <= 0)
			return (0);
	}
	return (1);
}

int	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

int	is_one_philo(t_philo *philo)
{
	if (philo->arg->philo_num == 1)
	{
		pthread_mutex_lock(&philo->arg->mutex_fork[philo->left_fork]);
		philo->arg->forks[philo->left_fork] = USING;
		printf_time(philo, "has taken a fork");
		philo->arg->forks[philo->left_fork] = NOTUSING;
		pthread_mutex_unlock(&philo->arg->mutex_fork[philo->left_fork]);
		return (1);
	}
	return (0);
}

void	print_die(t_philo *philo, int i)
{
	printf("%ld %d died\n", \
	get_time() - philo->arg->create_time, i + 1);
	philo->arg->is_die = 1;
	pthread_mutex_unlock(&philo->arg->mutex_global);
}
