/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:56:15 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/11 20:26:03 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_checker(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (!is_digit(av[i][j]))
				return (0);
		}
		if (ft_atoi(av[i]) == 0)
			return (0);
	}
	return (1);
}

int	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}
