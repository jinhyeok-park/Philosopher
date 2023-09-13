/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:23:18 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/11 20:29:34 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void	sem_print(t_philo_bonus *philo, char *str)
{
	sem_wait(philo->arg->sem_global);
	if (!philo->arg->is_die)
		printf("%ld %d %s\n", get_time() - philo->arg->create_time, \
		philo->id, str);
	sem_post(philo->arg->sem_global);
}

void	usleep_spliter(long time)
{
	long	end;

	end = get_time() + time;
	while (end > get_time())
		usleep(100);
}
