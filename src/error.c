/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:57:51 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/21 19:38:18 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_input_cnt(void)
{
    char    *str;
    int     len;
    int     i;

    str = "input value error\n";
    i = -1;
    len = 0;
    while (str[++i])
        len++;
    write(2, str, len);
}

void    error_common(void)
{
    char    *str;
    int     len;
    int     i;

    str = "error\n";
    i = -1;
    len = 0;
    while (str[++i])
        len++;
    write(2, str, len);
}