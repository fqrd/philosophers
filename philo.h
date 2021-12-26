/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:02:46 by fcaquard          #+#    #+#             */
/*   Updated: 2021/12/26 16:22:57 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_args
{
	size_t	philo;
	size_t	countdown;
	size_t	feeding;
	size_t	sleeping;
	size_t	limit;
}	t_args;

typedef struct timeval	t_timeval;
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		build_str(char *timestamp, char *philo, char *sentence);
int		ph_took_a_fork(size_t philo);
int		ph_eat(size_t philo);
int		ph_sleep(size_t philo);
int		ph_think(size_t philo);
int		ph_died(size_t philo);
#endif