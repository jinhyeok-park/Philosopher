/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:20:49 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/12 14:19:21 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_argument(int ac, char **av, t_argument *arg)
{
	arg->philo_num = ft_atoi(av[1]);
	arg->time_todie = ft_atol(av[2]);
	arg->time_toeat = ft_atol(av[3]);
	arg->time_tosleep = ft_atol(av[4]);
	arg->must_it_num = -1;
	arg->is_die = 0;
	if (ac == 6)
		arg->must_it_num = ft_atoi(av[5]);
	arg->create_time = get_time();
	return (1);
}

int	init_sem(t_argument *arg)
{
	sem_unlink(SEMFORK);
	sem_unlink(SEMGLOBAL);
	arg->sem_fork = sem_open(SEMFORK, O_CREAT, 0644, arg->philo_num);
	if (arg->sem_fork == SEM_FAILED)
		return (0);
	arg->sem_global = sem_open(SEMGLOBAL, O_CREAT, 0644, 1);
	if (arg->sem_global == SEM_FAILED)
		return (0);
	return (1);
}
