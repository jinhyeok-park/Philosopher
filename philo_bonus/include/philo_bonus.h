/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:51:28 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/09/13 14:33:52 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>

# define SEMFORK "fork"
# define SEMGLOBAL "global"

typedef struct s_argument
{
	int				philo_num;
	long			time_todie;
	long			time_toeat;
	long			time_tosleep;
	int				must_it_num;
	long			create_time;
	int				is_die;
	sem_t			*sem_fork;
	sem_t			*sem_global;
}	t_argument;

typedef struct s_philo_bonus
{
	int			id;
	int			eat_cnt;
	long		last_meal;
	t_argument	*arg;
}	t_philo_bonus;

int		philo_checker(int ac, char **av);
void	print_die(t_philo_bonus *philo);
int		is_digit(char c);
void	*thread_start(void *input);
void	sem_print(t_philo_bonus *philo, char *str);
long	get_time(void);
int		init_sem(t_argument *arg);
int		init_argument(int ac, char **av, t_argument *arg);
int		error_common(void);
long	ft_atol(char *str);
int		ft_atoi(char *str);
void	fork_error(void);
void	error_input_cnt(void);
void	usleep_spliter(long time);
void	*monitor(void *input);
void	child_destroy(t_argument *arg, pid_t *child_ids);
void	waiter(t_argument *arg, pid_t *child_ids);
void	child(t_argument *arg, int i);
void	sem_free(t_argument *arg);
int		waiter_2(t_argument *arg, pid_t *child_ids);
void	fork_start(pid_t **child_ids, t_argument *arg);
void	pickup_fork(t_philo_bonus *philo);
int		error_init_sem(void);
int		error_init_arg(void);

#endif