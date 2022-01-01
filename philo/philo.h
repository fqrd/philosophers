/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:02:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/01/01 19:52:09 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>	// write
# include <stdlib.h>	// malloc
# include <sys/time.h>	// timestamp
# include <pthread.h>	// threads

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
	pthread_mutex_t	fork_left;
	void			*fork_right;
	size_t			die_ct;
	size_t			feed_ct;
	size_t			sleep_ct;
	size_t			max_turns;
}	t_ph;

typedef struct s_args
{
	size_t	number;
	size_t	die_time;
	size_t	feed_time;
	size_t	sleep_time;
	size_t	feed_max;
}	t_args;

/** FUNCTIONS **/
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/** VERIF **/
int verifications(int argc, char *argv[]);

/** LISTS **/
t_list	*list_rewind(t_list *list);
void	clear_list(t_list **list);
void	clear_loop_list(size_t size, t_list **list);
t_list	*init_list(t_list **previous);

/** PHILO **/
typedef struct timeval	t_timeval;
int		build_str(char *timestamp, char *philo, char *sentence);
int		ph_took_a_fork(size_t philo);
int		ph_eat(size_t philo);
int		ph_sleep(size_t philo);
int		ph_think(size_t philo);
int		ph_died(size_t philo);


/** DEBUG **/
int	ph_releases_a_fork(size_t philo);
#endif