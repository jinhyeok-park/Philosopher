/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:21:29 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/07 11:25:28 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free(t_philo *philo)
{
	free(philo->arg->mutex_fork);
	free(philo->arg->forks);
	free(philo);
}
