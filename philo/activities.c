/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/08 16:42:07 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_took_a_fork(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "has taken a fork";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_eat(size_t philo, size_t duration, void **arg)
{
	char		*sentence;
	t_timeval	tv;

	// printf("eat: %ld\n", duration);


	sentence = "is eating";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
	{
		((t_ph *)(*arg))->timeout = tv.tv_usec + ((t_ph *)(*arg))->die_ct;
		ft_timeout((long int)duration + tv.tv_usec);
		return (1);
	}
	return (0);
}

int	ph_sleep(size_t philo, size_t duration)
{
	char		*sentence;
	t_timeval	tv;


	// printf("sleep: %ld\n", duration);

	sentence = "is sleeping";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
	{
		ft_timeout((long int)duration + tv.tv_usec);
		return (1);
	}
	return (0);
}

int	ph_think(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "is thinking";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_died(size_t philo)
{
	char		*sentence;
	t_timeval	tv;

	sentence = "died";
	if (gettimeofday(&tv, NULL) > -1
		&& build_str(ft_itoa(tv.tv_usec), ft_itoa(philo), sentence))
		return (1);
	return (0);
}
