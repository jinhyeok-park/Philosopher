/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:51:28 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/07 11:25:45 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define USING 1
# define NOTUSING 0

typedef struct s_argument
{
	int				philo_num;
	long			time_todie;
	long			time_toeat;
	long			time_tosleep;
	int				must_it_num;
	int				*forks;
	int				is_die;
	int				is_full;
	int				thread_count;
	int				monitor_start;
	long			create_time;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_global;
}	t_argument;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			eat_cnt;
	long		last_meal;
	pthread_t	thread_id;
	t_argument	*arg;
}	t_philo;

int		philo_checker(int ac, char **av);
void	usleep_spliter(long time);
int		is_digit(char c);
void	befor_monitor(t_philo *philo);
void	printf_time(t_philo *philo, char *str);
int		ft_atoi(char *str);
long	ft_atol(char *str);
void	mutex_init(t_argument *arg);
void	philo_eat(t_philo *philo);
int		init_philo(t_argument *arg, t_philo **philo);
int		init_argument(int ac, char **av, t_argument *arg);
int		philo_start(t_philo *philo, t_argument *arg);
void	*thread_start(void *input);
void	join_thread(t_philo *philo);
int		survive_check(t_philo *philo);
void	mutex_destroy(t_argument *arg);
void	thread_wait(t_philo *philo);
void	monitor(t_philo *philo);
long	get_time(void);
int		is_full_print(int is_full, t_philo *philo);
int		is_one_philo(t_philo *philo);
void	print_die(t_philo *philo, int i);
void	error_input_cnt(void);
int		error_init(void);
int		error_common(void);
void	philo_free(t_philo *philo);

#endif