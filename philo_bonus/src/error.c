/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:21:53 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/11 20:10:59 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_input_cnt(void)
{
	char	*str;
	int		len;
	int		i;

	str = "input value error\n";
	i = -1;
	len = 0;
	while (str[++i])
		len++;
	write(2, str, len);
}

int	error_common(void)
{
	char	*str;
	int		len;
	int		i;

	str = "error_check\n";
	i = -1;
	len = 0;
	while (str[++i])
		len++;
	return (write(2, str, len));
}

void	fork_error(void)
{
	write(2, "error_fork\n", 11);
	exit(1);
}

int	error_init_sem(void)
{
	return (write(2, "error_sem\n", 10));
}

int	error_init_arg(void)
{
	return (write(2, "error_arg\n", 10));
}
