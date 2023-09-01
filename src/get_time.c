/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:43:01 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/31 20:47:26 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long get_time(void)
{
    struct timeval time;
    long result;

    gettimeofday(&time, NULL);
    result = ((size_t)time.tv_sec * 1000) + ((size_t)time.tv_usec * 0.001);
    return result;
}
