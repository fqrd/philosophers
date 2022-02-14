/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:02:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/14 11:30:22 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>	// write
# include <stdlib.h>	// malloc
# include <sys/time.h>	// timestamp
# include <pthread.h>	// threads
# include <stdio.h>		// printf

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	void			*content;	
}	t_list;

typedef struct s_ph
{
	size_t			number;
	pthread_t		thread;
	pthread_mutex_t	death_protection;
	pthread_mutex_t	fork_left;
	void			*fork_right;
	int				died;
	int				sim_stop;
	int				all_ready;
	size_t			die_ct;
	size_t			feed_ct;
	size_t			sleep_ct;
	size_t			max_turns;
	size_t			time_of_death;
}	t_ph;

typedef struct s_args
{
	size_t	number;
	size_t	die_time;
	size_t	feed_time;
	size_t	sleep_time;
	size_t	feed_max;
}	t_args;

typedef struct timeval	t_timeval;

/** FUNCTIONS **/
int		ft_atoi(const char *str);

/** VERIF **/
int		preparation(int argc, char *argv[], t_args **args, t_list **list);

/** LISTS **/
void	clear_loop_list(size_t size, t_list **list, int clear_mutex);
t_list	*generate_list(t_args **args);

/** PHILO **/
int		ph_took_a_fork(t_ph **arg, size_t philo);
int		ph_eat(t_ph **arg, size_t philo, size_t duration);
int		ph_sleep(t_ph **arg, size_t philo, size_t duration);
int		ph_think(t_ph **arg, size_t philo);
int		ph_died(t_ph **arg, size_t philo);

/** TIME **/
size_t	timestamp_ms(void);
int		ft_pause(t_ph **arg, size_t duration);
int		still_alive(t_ph **arg);

/** PROGRAM **/
void	*runtime(void *arg);

#endif
