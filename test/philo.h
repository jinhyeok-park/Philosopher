/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:13:38 by euiclee           #+#    #+#             */
/*   Updated: 2023/09/05 13:51:52 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>

# define ARG_ERROR "Yo man, it's error\n"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			who;
	int			eat_count;
	int			left;
	int			right;
	uint64_t	last_ate;
	t_table		*table;
	pthread_t	chair;
}t_philo;

struct s_table
{
	int				die;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	uint64_t		start_time;
	t_philo			*philo;
	pthread_mutex_t	m_check;
	pthread_mutex_t	m_last_ate;
	pthread_mutex_t	*forks;
};

/*main*/
int			main(int ac, char **av);
int			init_mutex(t_table *table);
int			init_philo(t_table *table);
int			init_arg(int ac, char **av, t_table *table);

/*philosophy_club*/
void		monitor(t_table *table);
void		end_philo_club(t_table *table);
int			start_philo_club(t_table *table);

/*philosopher*/
void		*routine(void *arg);
void		philo_eat(t_philo *philo, t_table *table);
void		philo_sleep(t_philo *philo, t_table *table);
void		philo_print(char *str, t_philo *philo, t_table *table);

/*utils*/
uint64_t	gettime(void);
int			ft_atoi(char *str);
int			ft_strlen(char *str);
void		msleep(uint64_t sleep_ms);
void		free_all(t_table *table);

#endif