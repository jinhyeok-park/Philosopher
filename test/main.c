/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:09:41 by euiclee           #+#    #+#             */
/*   Updated: 2023/09/05 15:11:13 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	free_all(t_table *table)
{
	free(table->forks);
	free(table->philo);
}

void	msleep(uint64_t sleep_ms)
{
	uint64_t	start_ms;

	start_ms = gettime();
	while (gettime() - start_ms < sleep_ms)
		usleep(100);
}

uint64_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi(char *str)
{
	size_t	ret;
	size_t	idx;

	ret = 0;
	idx = 0;
	while (str[idx])
	{
		if (str[idx] >= '0' && str[idx] <= '9')
			ret = ret * 10 + (str[idx] - '0');
		else
			return (-1);
		idx++;
	}
	if (ret > INT_MAX)
		return (-1);
	return (ret);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->who % 2)
		usleep(table->n_philo * 42);
	while (1)
	{
		pthread_mutex_lock(&table->m_check);
		if (table->die == 1 || philo->eat_count >= table->must_eat)
		{
			pthread_mutex_unlock(&table->m_check);
			break ;
		}
		pthread_mutex_unlock(&table->m_check);
		philo_eat(philo, table);
		philo_sleep(philo, table);
		philo_print("is thinking", philo, table);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->forks[philo->left]);
	pthread_mutex_lock(&table->forks[philo->right]);
	philo_print("has taken a fork", philo, table);
	//pthread_mutex_lock(&table->m_last_ate);
	philo_print("is eating", philo, table);
	pthread_mutex_lock(&table->m_check);
	philo->last_ate = gettime();
	philo->eat_count++;
	pthread_mutex_unlock(&table->m_check);
	//pthread_mutex_unlock(&table->m_last_ate);
	msleep(table->t_eat);
	pthread_mutex_unlock(&table->forks[philo->right]);
	pthread_mutex_unlock(&table->forks[philo->left]);
}

void	philo_sleep(t_philo *philo, t_table *table)
{
	philo_print("is sleeping", philo, table);
	msleep(table->t_sleep);
}

void	philo_print(char *str, t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->m_check);
	if (table->die != 1)
		printf("%llu %d %s\n", gettime() - table->start_time, philo->who, str);
	pthread_mutex_unlock(&table->m_check);
}

void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->n_philo)
		{
			//pthread_mutex_lock(&table->m_last_ate);
				pthread_mutex_unlock(&table->m_check);
			if (gettime() - table->philo[i].last_ate >= (uint64_t)table->t_die)
			{
				//pthread_mutex_lock(&table->m_check);
				table->die = 1;
				if (table->philo[i].eat_count < table->must_eat)
					printf("%llu %d died\n",
						gettime() - table->start_time, table->philo[i].who);
				pthread_mutex_unlock(&table->m_check);
				//pthread_mutex_unlock(&table->m_last_ate);
				return ;
			}
				pthread_mutex_unlock(&table->m_check);
			//pthread_mutex_unlock(&table->m_last_ate);
			usleep(100);
		}
	}
}

void	end_philo_club(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->m_check);
	pthread_mutex_destroy(&table->m_last_ate);
	free_all(table);
}

int	start_philo_club(t_table *table)
{
	int	i;

	i = -1;
	table->die = 0;
	table->start_time = gettime();
	while (++i < table->n_philo)
	{
		table->philo[i].last_ate = table->start_time;
		if (pthread_create(&table->philo[i].chair,
				NULL, routine, &table->philo[i]))
			return (1);
	}
	monitor(table);
	i = -1;
	if (table->n_philo == 1)
		pthread_detach(table->philo[++i].chair);
	else
		while (++i < table->n_philo)
			pthread_join(table->philo[i].chair, NULL);
	end_philo_club(table);
	return (0);
}

int	init_arg(int ac, char **av, t_table *table)
{
	table->n_philo = ft_atoi(av[1]);
	table->t_die = ft_atoi(av[2]);
	table->t_eat = ft_atoi(av[3]);
	table->t_sleep = ft_atoi(av[4]);
	table->must_eat = INT_MAX;
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	if (table->n_philo <= 0 || table->t_die <= 0 || table->t_eat <= 0
		|| table->t_sleep <= 0 || table->must_eat == -1)
		return (1);
	else
		return (0);
}

int	init_mutex(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (1);
	i = -1;
	while (++i < table->n_philo)
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (free_all(table), 1);
	if (pthread_mutex_init(&table->m_check, NULL))
		return (free_all(table), 1);
	if (pthread_mutex_init(&table->m_last_ate, NULL))
		return (free_all(table), 1);
	return (0);
}

int	init_philo(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
		return (free_all(table), 1);
	i = -1;
	while (++i < table->n_philo)
	{
		table->philo[i].who = i + 1;
		table->philo[i].eat_count = 0;
		table->philo[i].left = i;
		table->philo[i].right = (i + 1) % table->n_philo;
		table->philo[i].eat_count = 0;
		table->philo[i].table = table;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (write(2, ARG_ERROR, ft_strlen(ARG_ERROR)));
	if (init_arg(ac, av, &table))
		return (write(2, ARG_ERROR, ft_strlen(ARG_ERROR)));
	if (init_mutex(&table))
		return (write(2, ARG_ERROR, ft_strlen(ARG_ERROR)));
	if (init_philo(&table))
		return (write(2, ARG_ERROR, ft_strlen(ARG_ERROR)));
	if (start_philo_club(&table))
		return (write(2, ARG_ERROR, ft_strlen(ARG_ERROR)));
	return (0);
}
