/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:42:41 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/21 20:51:56 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(char *str)
{
    int i;
    int ret;

    i = -1;
    ret = 0;
    while (str[++i])
        ret += (ret * 10) + str[i] - '0';
    return (ret);
}

// int ft_strlen(char *str)
// {
//     int i;
//     int len;

//     i = -1;
//     while (str[++i])
//         len++;
//     return (len);
// }