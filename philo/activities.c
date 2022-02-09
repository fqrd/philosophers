/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/09 20:43:10 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_took_a_fork(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "has taken a fork";
	while (gettimeofday(&tv, NULL) == -1) ;
	if (build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_eat(size_t philo, size_t duration)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "is eating";
	while (gettimeofday(&tv, NULL) == -1) ;
	if (build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
	{
		return (ft_timeout(duration));
	}
	return (0);
}

int	ph_sleep(size_t philo, size_t duration)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "is sleeping";
	while (gettimeofday(&tv, NULL) == -1) ;
	if (build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
	{
		return (ft_timeout(duration));
	}
	return (0);
}

int	ph_think(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "is thinking";
	while (gettimeofday(&tv, NULL) == -1) ;
	if (build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_died(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "died";
	while (gettimeofday(&tv, NULL) == -1) ;
	if (build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}
