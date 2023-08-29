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
		philo_start(philo, &arg);
		monitor(philo);
		mutex_destroy(&arg);
		int	i;

		i = -1;
		while (++i < philo->arg->philo_num)
		{
			pthread_join(philo[i].thread_id, NULL);
		}
	}
	else
		error_input_cnt();

}

void	monitor(t_philo *philo)
{
	int		i;
	long	cur_time;

	while (1)
	{
		i = -1;
		while (++i < philo->arg->philo_num)
		{
			printf("monitoring...\n %d eat cnt is %d\n", philo[i].id, philo[i].eat_cnt);
			cur_time = get_time();
			printf("%ld\n", cur_time);
			printf("%ld\n", philo[i].last_meal);
			printf("%ld %d\n", cur_time - philo[i].last_meal, philo->arg->time_todie);
			if (cur_time - philo[i].last_meal > philo->arg->time_todie)
			{
				printf("die\n");
				philo->arg->is_die = 1;
				return ;
			}
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
	printf("%ld %d %s\n", (cur_time - philo->arg->create_time), philo->id, str);
	pthread_mutex_unlock(&philo->arg->mutex_global);
}

void	*thread_start(void *input)
{
	t_philo *philo;

	philo = (t_philo *)input;
	if (philo->id % 2 == 0)
		sleep(1000);
	while (!philo->arg->is_die)
	{
		// pthread_mutex_lock(&philo->arg->mutex_fork[philo->left_fork]);
		// philo->arg->forks[philo->left_fork] = USING;
		// printf("%d", philo->id);
		// printf_time(philo, "is pick up fork\n");
		// pthread_mutex_lock(&philo->arg->mutex_fork[philo->right_fork]);
		// philo->arg->forks[philo->right_fork] = USING;
		// philo->last_meal = get_time();
		// printf("%d", philo->id);
		// printf_time(philo, "is pick up fork\n");
		// printf("%d", philo->id);
		// printf_time(philo, "is eating..\n");
		// pthread_mutex_lock(&philo->arg->mutex_global);
		// philo->eat_cnt++;
		// pthread_mutex_unlock(&philo->arg->mutex_global);
		// usleep(philo->arg->time_toeat);
		// philo->arg->forks[philo->right_fork] = NOTUSING;
		// pthread_mutex_unlock(&philo->arg->mutex_fork[philo->right_fork]);
		// philo->arg->forks[philo->left_fork] = NOTUSING;
		// pthread_mutex_unlock(&philo->arg->mutex_fork[philo->left_fork]);
		// usleep(philo->arg->time_tosleep);
		pthread_mutex_lock(&philo->arg->mutex_global);
		printf("cnt up");
		philo->last_meal = get_time();
		philo->eat_cnt++;
		pthread_mutex_unlock(&philo->arg->mutex_global);
	}
	return (NULL);
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
	arg->time_todie = ft_atoi(av[2]);
	arg->time_toeat = ft_atoi(av[3]);
	arg->time_tosleep = ft_atoi(av[4]);
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
