/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 00:26:42 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_took_a_fork(size_t philo)
{
	char		*sentence;

	sentence = "has taken a fork";
	if (build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_eat(size_t philo, size_t duration)
{
	char		*sentence;

	sentence = "is eating";
	if (build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), sentence))
	{
		return (ft_pause(duration));
	}
	return (0);
}

int	ph_sleep(size_t philo, size_t duration)
{
	char		*sentence;

	sentence = "is sleeping";
	if (build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), sentence))
	{
		return (ft_pause(duration));
	}
	return (0);
}

int	ph_think(size_t philo)
{
	char		*sentence;

	sentence = "is thinking";
	if (build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), sentence))
		return (1);
	return (0);
}

int	ph_died(size_t philo)
{
	char		*sentence;

	sentence = "died";
	if (build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), sentence))
		return (1);
	return (0);
}
