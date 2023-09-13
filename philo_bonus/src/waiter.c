/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:27:34 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/13 14:47:09 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	waiter(t_argument *arg, pid_t *child_ids)
{
	if (arg->must_it_num != -1)
	{
		while (1)
		{
			if (waiter_2(arg, child_ids))
				return ;
		}
	}
}

int	waiter_2(t_argument *arg, pid_t *child_ids)
{
	pid_t	result;
	int		full_count;
	int		status;
	int		i;

	status = 0;
	i = -1;
	result = 0;
	full_count = 0;
	while (++i < arg->philo_num)
	{
		result = waitpid(child_ids[i], &status, 0);
		if (result > 0 && WEXITSTATUS(status) == 2)
			full_count++;
		else if (result > 0 && WEXITSTATUS(status) == 1)
			return (1);
	}
	if (full_count >= arg->philo_num)
	{
		printf("%ld philo full\n", get_time() - arg->create_time);
		sem_free(arg);
		free(child_ids);
		exit(0);
	}
	return (0);
}
