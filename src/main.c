/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:53:10 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/24 18:43:38by jinhyeok         ###   ########.fr       */
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
		init_argument(ac, av, &arg);
		init_philo(&arg, &philo);
		for (int i = 0 ; i < philo->arg->philo_num ; i++)
		{
			printf("%d id, %d left %d right\n", philo[i].id, philo[i].left_fork , philo[i].right_fork);
		}
		// exit(1);
		philo_start(philo, &arg);
		monitor(philo);
		mutex_destroy(&arg);
		int	i;

		i = -1;
		while (++i < philo->arg->philo_num)
			pthread_join(philo[i].thread_id, NULL);
	}
	else
		error_input_cnt();

}

void	monitor(t_philo *philo)
{
	int		i;
	int		j;
	long	cur_time;

	while (1)
	{
		i = -1;
		while (++i < philo->arg->philo_num)
		{
			pthread_mutex_lock(&philo->arg->mutex_global);
			cur_time = get_time();
			if ((cur_time - philo[i].last_meal) > philo[i].arg->time_todie)
			{
				printf("%ld %d died\n", (cur_time - philo[i].last_meal), i + 1);
				j = -1;
				while (++j < philo->arg->philo_num)
					philo[j].arg->is_die = 1;
				pthread_mutex_unlock(&philo->arg->mutex_global);
				return ;
			}
			pthread_mutex_unlock(&philo->arg->mutex_global);
		}
	}
}

void	mutex_destroy(t_argument *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_num)
		pthread_mutex_destroy(&arg->mutex_fork[i]);
	pthread_mutex_destroy(&arg->mutex_global);
}

void	printf_time(t_philo *philo, char *str)
{
	long	cur_time;

	cur_time = get_time();
	pthread_mutex_lock(&philo->arg->mutex_global);
	if (!philo->arg->is_die)
		printf("%ld %d %s\n", (cur_time - philo->arg->create_time), philo->id, str);
	pthread_mutex_unlock(&philo->arg->mutex_global);
}

void	*thread_start(void *input)
{
	t_philo *philo;
	int	i;

	philo = (t_philo *)input;
	i = 0;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!survive_check(philo))
			break;

		pthread_mutex_lock(&philo->arg->mutex_fork[philo->left_fork]);

		printf_time(philo, "is pick up");
		philo->arg->forks[philo->left_fork] = USING;

		pthread_mutex_lock(&philo->arg->mutex_fork[philo->right_fork]);
		printf_time(philo, "is pick up");
		philo->arg->forks[philo->right_fork] = USING;

		printf_time(philo, "is eating");
		pthread_mutex_lock(&philo->arg->mutex_global);
		philo->eat_cnt += 1;
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->arg->mutex_global);
		usleep(philo->arg->time_toeat * 1000);

		printf_time(philo, "is sleeping");
		usleep(philo->arg->time_tosleep * 1000);
		printf_time(philo, "is thinking");
		philo->arg->forks[philo->right_fork] = NOTUSING;
		pthread_mutex_unlock(&philo->arg->mutex_fork[philo->right_fork]);
		philo->arg->forks[philo->left_fork] = NOTUSING;
		pthread_mutex_unlock(&philo->arg->mutex_fork[philo->left_fork]);
	}
	pthread_mutex_unlock(&philo->arg->mutex_global);
	return NULL;
}

int	survive_check(t_philo *philo)
{
	int result;
    pthread_mutex_lock(&philo->arg->mutex_global);
    result = !philo->arg->is_die;
    pthread_mutex_unlock(&philo->arg->mutex_global);
    return result;
}

int	philo_start(t_philo *philo, t_argument *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_num)
		pthread_create(&philo[i].thread_id, NULL, thread_start, (void*)&philo[i]);
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
		(*philo)[i].status = 0;
		(*philo)[i].left_hand = 0;
		(*philo)[i].right_hand = 0;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % arg->philo_num;
		(*philo)[i].thread_id = 0;
		(*philo)[i].arg = arg;
		(*philo)[i].eat_cnt = 0;
		(*philo)[i].last_meal = get_time();
	}
	return (1);
}

void	init_argument(int ac, char **av, t_argument *arg)
{
	int	i;

	i = -1;
	arg->philo_num = ft_atoi(av[1]);
	arg->time_todie = ft_atol(av[2]);
	arg->time_toeat = ft_atol(av[3]);
	arg->time_tosleep = ft_atol(av[4]);
	if (ac == 6)
		arg->must_it_num = ft_atoi(av[5]);
	else
		arg->must_it_num = -1;
	arg->create_time = get_time();
	arg->forks = malloc(sizeof(int) * arg->philo_num);
	arg->mutex_fork = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	pthread_mutex_init(&arg->mutex_global, NULL);
	while (++i < arg->philo_num)
	{
		arg->forks[i] = 0;
		pthread_mutex_init(&arg->mutex_fork[i], NULL);
	}
}
