/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:04:02 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/13 14:30:00 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_wait(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->arg->mutex_global);
		if (philo->arg->philo_num == philo->arg->thread_count)
		{
			pthread_mutex_unlock(&philo->arg->mutex_global);
			break ;
		}
		pthread_mutex_unlock(&philo->arg->mutex_global);
	}
	pthread_mutex_lock(&philo->arg->mutex_global);
	philo->last_meal = get_time();
	philo->arg->create_time = philo->last_meal;
	philo->arg->monitor_start = 1;
	pthread_mutex_unlock(&philo->arg->mutex_global);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->mutex_fork[philo->left_fork]);
	philo->arg->forks[philo->left_fork] = USING;
	printf_time(philo, "has taken a fork");
	pthread_mutex_lock(&philo->arg->mutex_fork[philo->right_fork]);
	philo->arg->forks[philo->right_fork] = USING;
	printf_time(philo, "has taken a fork");
	printf_time(philo, "is eating");
	pthread_mutex_lock(&philo->arg->mutex_global);
	philo->last_meal = get_time();
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->arg->mutex_global);
	usleep_spliter(philo->arg->time_toeat);
}

void	*thread_start(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	thread_wait(philo);
	if (philo->id & 1)
		usleep(philo->arg->philo_num * 42);
	while (1)
	{
		if (!survive_check(philo))
			break ;
		if (is_one_philo(philo))
			break ;
		philo_eat(philo);
		philo->arg->forks[philo->right_fork] = NOTUSING;
		pthread_mutex_unlock(&philo->arg->mutex_fork[philo->right_fork]);
		philo->arg->forks[philo->left_fork] = NOTUSING;
		pthread_mutex_unlock(&philo->arg->mutex_fork[philo->left_fork]);
		printf_time(philo, "is sleeping");
		usleep_spliter(philo->arg->time_tosleep);
		printf_time(philo, "is thinking");
	}
	return (NULL);
}

int	survive_check(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->arg->mutex_global);
	result = !philo->arg->is_die;
	if (philo->arg->must_it_num != -1 && \
	philo->eat_cnt >= philo->arg->must_it_num)
		result = 0;
	pthread_mutex_unlock(&philo->arg->mutex_global);
	return (result);
}

int	philo_start(t_philo *philo, t_argument *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_num)
	{
		if (pthread_create(&philo[i].thread_id, NULL, \
		thread_start, (void *)&philo[i]))
			return (0);
		pthread_mutex_lock(&philo->arg->mutex_global);
		philo->arg->thread_count++;
		pthread_mutex_unlock(&philo->arg->mutex_global);
	}
	return (1);
}
