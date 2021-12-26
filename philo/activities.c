/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2021/12/26 16:10:03 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_took_a_fork(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "has taken a fork";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_sec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_eat(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "is eating";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_sec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_sleep(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "is sleeping";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_sec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_think(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "is thinking";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_sec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_died(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "died";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_sec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}