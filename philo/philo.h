/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:02:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/19 15:27:00 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

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
	pthread_mutex_t	*fork_right;
	int				died;
	int				sim_stop;
	int				all_ready;
	size_t			time_of_death;
	struct s_args	*args;
}	t_ph;

typedef struct s_args
{
	size_t			number;
	size_t			die_time;
	size_t			feed_time;
	size_t			sleep_time;
	size_t			feed_max;
	pthread_mutex_t	write_mutex;

}	t_args;

typedef struct timeval	t_timeval;

/** FUNCTIONS **/
int		ft_atoi(const char *str);

/** VERIF **/
int		preparation(int argc, char *argv[], t_args **args, t_list **list);

/** LISTS **/
t_list	*generate_list(t_args **args);

/** PHILO **/
int		ph_took_a_fork(t_ph **content, size_t philo);
int		ph_eat(t_ph **content, size_t philo, size_t duration);
int		ph_sleep(t_ph **content, size_t philo, size_t duration);
int		ph_think(t_ph **content, size_t philo);
int		ph_died(t_ph **content, size_t philo);

/** TIME **/
size_t	timestamp_ms(void);
int		ft_pause(t_ph **content, size_t duration);
int		still_alive(t_ph **content);

/** PROGRAM **/
void	*runtime(void *arg);

/** CLEAN **/
int		clear(t_list **list, t_args **args);
#endif
