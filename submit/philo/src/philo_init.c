/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:53:36 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/06 19:53:56 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_argument *arg, t_philo **philo)
{
	int	i;

	i = -1;
	(*philo) = malloc(sizeof(t_philo) * (arg->philo_num));
	if (!(*philo))
		return (0);
	while (++i < arg->philo_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % arg->philo_num;
		(*philo)[i].thread_id = 0;
		(*philo)[i].arg = arg;
		(*philo)[i].eat_cnt = 0;
		(*philo)[i].last_meal = get_time();
	}
	return (1);
}

int	init_argument(int ac, char **av, t_argument *arg)
{
	int	i;

	i = -1;
	arg->philo_num = ft_atoi(av[1]);
	arg->time_todie = ft_atol(av[2]);
	arg->time_toeat = ft_atol(av[3]);
	arg->time_tosleep = ft_atol(av[4]);
	arg->is_die = 0;
	arg->is_full = 0;
	arg->monitor_start = 0;
	arg->thread_count = 0;
	arg->must_it_num = -1;
	if (ac == 6)
		arg->must_it_num = ft_atoi(av[5]);
	arg->create_time = get_time();
	arg->forks = malloc(sizeof(int) * arg->philo_num);
	if (!arg->forks)
		return (0);
	arg->mutex_fork = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!arg->mutex_fork)
	{
		free(arg->forks);
		return (0);
	}
	return (1);
}

void	mutex_init(t_argument *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_num)
	{
		arg->forks[i] = 0;
		pthread_mutex_init(&arg->mutex_fork[i], NULL);
	}
	pthread_mutex_init(&arg->mutex_global, NULL);
}
