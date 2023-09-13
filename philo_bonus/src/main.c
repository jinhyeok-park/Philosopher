/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:53:10 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/13 14:41:24 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_argument		arg;
	pid_t			*child_ids;

	child_ids = NULL;
	if (ac >= 5 && ac <= 6)
	{
		if (!philo_checker(ac, av))
			return (error_common());
		if (!init_argument(ac, av, &arg))
			return (error_init_arg());
		if (!init_sem(&arg))
			return (error_init_sem());
		fork_start(&child_ids, &arg);
	}
	else
	{
		error_input_cnt();
		exit(1);
	}
	waiter(&arg, child_ids);
	child_destroy(&arg, child_ids);
	free(child_ids);
	sem_free(&arg);
}

void	child_destroy(t_argument *arg, pid_t *child_ids)
{
	int		status;
	pid_t	result;
	int		i;
	int		child_status;
	int		temp;

	status = 0;
	while (1)
	{
		i = -1;
		while (++i < arg->philo_num)
		{
			result = waitpid(child_ids[i], &child_status, WNOHANG);
			if (result > 0 && WIFEXITED(child_status) == 1)
			{
				temp = i;
				i = -1;
				while (++i < arg->philo_num)
					kill(child_ids[i], SIGTERM);
				printf("%ld %d is died\n", get_time() - arg->create_time, \
				temp + 1);
				return ;
			}
		}
	}
}

void	*monitor(void *input)
{
	t_philo_bonus	*philo;

	philo = (t_philo_bonus *)input;
	while (1)
	{
		sem_wait(philo->arg->sem_global);
		if (get_time() - philo->last_meal > philo->arg->time_todie)
		{
			philo->arg->is_die = 1;
			sem_post(philo->arg->sem_global);
			exit(1);
		}
		else if (philo->arg->must_it_num == philo->eat_cnt)
		{
			philo->arg->is_die = 1;
			sem_post(philo->arg->sem_global);
			sem_post(philo->arg->sem_fork);
			sem_post(philo->arg->sem_fork);
			exit(2);
		}
		sem_post(philo->arg->sem_global);
		usleep(100);
	}
}

void	print_die(t_philo_bonus *philo)
{
	printf("%ld %d died\n", \
	get_time() - philo->arg->create_time, philo->id);
	philo->arg->is_die = 1;
	sem_post(philo->arg->sem_global);
}

void	pickup_fork(t_philo_bonus *philo)
{
	sem_wait(philo->arg->sem_fork);
	sem_print(philo, "has taken a fork");
	sem_wait(philo->arg->sem_fork);
	sem_print(philo, "has taken a fork");
	sem_print(philo, "is eating");
	sem_wait(philo->arg->sem_global);
	philo->last_meal = get_time();
	sem_post(philo->arg->sem_global);
	usleep_spliter(philo->arg->time_toeat);
	sem_wait(philo->arg->sem_global);
	philo->eat_cnt++;
	sem_post(philo->arg->sem_global);
	sem_post(philo->arg->sem_fork);
	sem_post(philo->arg->sem_fork);
}
