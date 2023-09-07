/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:53:10 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/06 18:57:48 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
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
			return (1);
		init_philo(&arg, &philo);
		philo_start(philo, &arg);
		while (1)
		{
			pthread_mutex_lock(&philo->arg->mutex_global);
			if (philo->arg->monitor_start)
			{
				pthread_mutex_unlock(&philo->arg->mutex_global);
				break ;
			}
			pthread_mutex_unlock(&philo->arg->mutex_global);
		}
		monitor(philo);
		join_thread(philo);
		mutex_destroy(&arg);
	}
	else
		error_input_cnt();
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
	pthread_mutex_destroy(&arg->mutex_last_meal);
}

void	printf_time(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->arg->mutex_global);
	if (!philo->arg->is_die)
		printf("%ld %d %s\n", (get_time() - philo->arg->create_time), philo->id, str);
	pthread_mutex_unlock(&philo->arg->mutex_global);
}

void	monitor(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < philo->arg->philo_num)
		{
			pthread_mutex_lock(&philo->arg->mutex_global);
			if ( get_time() - philo->arg->create_time > philo->arg->time_todie && \
			get_time() - philo[i].last_meal > philo->arg->time_todie)
			{
				printf("%ld %d died\n", get_time() - philo->arg->create_time, i + 1);
				philo->arg->is_die = 1;
				pthread_mutex_unlock(&philo->arg->mutex_global);
				return ;
			}
			pthread_mutex_unlock(&philo->arg->mutex_global);
		}
	}
}

void	thread_wait(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->arg->mutex_global);
		if (philo->arg->philo_num == philo->arg->thread_count)
		{
			pthread_mutex_unlock(&philo->arg->mutex_global);
			break;
		}
		pthread_mutex_unlock(&philo->arg->mutex_global);
	}
	pthread_mutex_lock(&philo->arg->mutex_global);
	philo->last_meal = get_time();
	philo->arg->create_time = philo->last_meal;
	philo->arg->monitor_start = 1;
	pthread_mutex_unlock(&philo->arg->mutex_global);
}

// int		survive_check(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->arg->mutex_global);
// 	if (philo->arg->is_die)
// 	{
// 		pthread_mutex_unlock(&philo->arg->mutex_global);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->arg->mutex_global);
// 	return (0);
// }

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
	t_philo *philo;
	
	philo = (t_philo *)input;
	thread_wait(philo);
	if (philo->id & 1)
		usleep(philo->arg->philo_num * 42);
	while (1)
	{
		if (!survive_check(philo))
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

void	usleep_spliter(long time)
{
	long end;

	end = get_time() + time;
	while (end > get_time())
		usleep(100);
}

int	survive_check(t_philo *philo)
{
	int	result;

    pthread_mutex_lock(&philo->arg->mutex_global);
    result = !philo->arg->is_die;
    pthread_mutex_unlock(&philo->arg->mutex_global);
    return (result);
}

int	philo_start(t_philo *philo, t_argument *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_num)
	{
		philo[i].last_meal = get_time();
		pthread_create(&philo[i].thread_id, NULL, thread_start, (void*)&philo[i]);
		pthread_mutex_lock(&philo->arg->mutex_global);
		philo->arg->thread_count++;
		pthread_mutex_unlock(&philo->arg->mutex_global);
	}
	return (1);
}

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
	if (ac == 6)
		arg->must_it_num = ft_atoi(av[5]);
	else
		arg->must_it_num = -1;
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
	pthread_mutex_init(&arg->mutex_global, NULL);
	pthread_mutex_init(&arg->mutex_last_meal, NULL);
	while (++i < arg->philo_num)
	{
		arg->forks[i] = 0;
		pthread_mutex_init(&arg->mutex_fork[i], NULL);
	}
	return (1);
}
