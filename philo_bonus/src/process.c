/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:15:17 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/12 10:59:08 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*thread_start(void *input)
{
	t_philo_bonus	*philo;

	philo = input;
	if (philo->id & 1)
		usleep(philo->arg->philo_num * 42);
	while (1)
	{
		sem_wait(philo->arg->sem_global);
		if (philo->arg->is_die)
			break ;
		sem_post(philo->arg->sem_global);
		pickup_fork(philo);
		sem_print(philo, "is sleeping");
		usleep_spliter(philo->arg->time_tosleep);
		sem_print(philo, "is thinking");
	}
	return (NULL);
}

void	fork_start(pid_t **child_ids, t_argument *arg)
{
	int		i;
	pid_t	id;

	(*child_ids) = malloc(sizeof(pid_t) * arg->philo_num);
	if (!child_ids)
	{
		write(2, "malloc_error\n", 13);
		exit(1);
	}
	i = -1;
	while (++i < arg->philo_num)
	{
		id = fork();
		if (id == 0)
			child(arg, i);
		else if (id > 0)
			(*child_ids)[i] = id;
		else
			fork_error();
	}
}

void	child(t_argument *arg, int i)
{
	t_philo_bonus	philo;
	pthread_t		thread;

	philo.eat_cnt = 0;
	philo.last_meal = get_time();
	philo.id = i + 1;
	philo.arg = arg;
	pthread_create(&thread, NULL, monitor, (void *)&philo);
	thread_start(&philo);
	pthread_join(thread, NULL);
	exit(1);
}

void	sem_free(t_argument *arg)
{
	sem_close(arg->sem_global);
	sem_close(arg->sem_fork);
	sem_unlink(SEMFORK);
	sem_unlink(SEMGLOBAL);
}
