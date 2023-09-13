/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:57:51 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/06 19:57:56 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	error_init(void)
{
	return (write(2, "error_init\n", 11));
}
