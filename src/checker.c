/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   d: 2023/08/21 19:51:29 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/21 21:02:01 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_checker(int ac, char **av)
{
    int i;
    int j;

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

int is_digit(char c)
{
    return (c >= 48 && c <= 57);
}
