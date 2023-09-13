/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:42:41 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/13 14:28:49 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (str[++i])
		ret = (ret * 10) + str[i] - '0';
	return (ret);
}

long	ft_atol(char *str)
{
	int		i;
	long	ret;

	i = -1;
	ret = 0;
	while (str[++i])
		ret = (ret * 10) + (str[i] - '0');
	return (ret);
}

void	usleep_spliter(long time)
{
	long	end;

	end = get_time() + time;
	while (end > get_time())
		usleep(100);
}

void	printf_time(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->arg->mutex_global);
	if (!philo->arg->is_die)
		printf("%ld %d %s\n", (get_time() - philo->arg->create_time), \
	philo->id, str);
	pthread_mutex_unlock(&philo->arg->mutex_global);
}

int	is_full_print(int is_full, t_philo *philo)
{
	pthread_mutex_unlock(&philo->arg->mutex_global);
	if (is_full == philo->arg->philo_num)
	{
		pthread_mutex_lock(&philo->arg->mutex_global);
		printf("%ld philo is full\n", get_time() - philo->arg->create_time);
		philo->arg->is_die = 1;
		pthread_mutex_unlock(&philo->arg->mutex_global);
		return (1);
	}
	return (0);
}
