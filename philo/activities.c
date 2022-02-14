/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/14 16:03:55 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_took_a_fork(t_ph **arg, size_t philo)
{
	if (!still_alive(arg))
		return (0);
	printf("%ld %ld has taken a fork\n", timestamp_ms(), philo);
	return (1);
}

int	ph_eat(t_ph **arg, size_t philo, size_t duration)
{
	size_t	time;

	if (pthread_mutex_lock(&(*arg)->death_protection) == 0)
	{
		// printf("%ld eat: mutex locked\n", philo);
		if (!still_alive(arg))
			return (0);
		time = timestamp_ms();
		(*arg)->time_of_death = time + (*arg)->die_ct;
		printf("%ld %ld is eating\n", time, philo);
		while (pthread_mutex_unlock(&(*arg)->death_protection) != 0)
			;
		// printf("%ld eat: mutex unlocked\n", philo);
		ft_pause(arg, duration);
	}
	return (1);
}

int	ph_sleep(t_ph **arg, size_t philo, size_t duration)
{
	if (!still_alive(arg))
		return (0);
	printf("%ld %ld is sleeping\n", timestamp_ms(), philo);
	ft_pause(arg, duration);
	return (1);
}

int	ph_think(t_ph **arg, size_t philo)
{
	if (!still_alive(arg))
		return (0);
	printf("%ld %ld is thinking\n", timestamp_ms(), philo);
	return (1);
}

int	ph_died(t_ph **arg, size_t philo)
{
	(*arg)->died = 1;
	printf("%ld %ld died\n", timestamp_ms(), philo);
	return (1);
}
