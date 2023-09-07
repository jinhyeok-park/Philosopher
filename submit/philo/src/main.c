/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:53:10 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/07 11:24:59 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_argument	arg;
	t_philo		*philo;

	if (ac >= 5 && ac <= 6)
	{
		if (!philo_checker(ac, av))
		{
			error_common();
			return (1);
		}
		if (!init_argument(ac, av, &arg))
			return (error_init());
		if (!init_philo(&arg, &philo))
			return (error_init());
		mutex_init(&arg);
		philo_start(philo, &arg);
		befor_monitor(philo);
		monitor(philo);
		join_thread(philo);
		mutex_destroy(&arg);
		philo_free(philo);
	}
	else
		error_input_cnt();
}

void	befor_monitor(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->arg->mutex_global);
		if (philo->arg->monitor_start)
		{
			pthread_mutex_unlock(&philo->arg->mutex_global);
			return ;
		}
		pthread_mutex_unlock(&philo->arg->mutex_global);
	}
}

void	join_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->arg->philo_num)
		pthread_join(philo[i].thread_id, NULL);
}

void	mutex_destroy(t_argument *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_num)
		pthread_mutex_destroy(&arg->mutex_fork[i]);
	pthread_mutex_destroy(&arg->mutex_global);
}

void	monitor(t_philo *philo)
{
	int	i;
	int	is_full;

	while (1)
	{
		i = -1;
		is_full = 0;
		while (++i < philo->arg->philo_num)
		{
			pthread_mutex_lock(&philo->arg->mutex_global);
			if ((get_time() - philo->arg->create_time > philo->arg->time_todie \
			&& get_time() - philo[i].last_meal > philo->arg->time_todie))
			{
				print_die(philo, i);
				return ;
			}
			else if (philo->arg->must_it_num == philo[i].eat_cnt)
				is_full++;
			pthread_mutex_unlock(&philo->arg->mutex_global);
		}
		if (is_full_print(is_full, philo))
			return ;
	}
}
