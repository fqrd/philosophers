/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/19 15:19:44 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_took_a_fork(t_ph **content, size_t philo)
{
	if (!still_alive(content))
		return (0);
	printf("%ld %ld has taken a fork\n", timestamp_ms(), philo);
	return (1);
}

int	ph_eat(t_ph **content, size_t philo, size_t duration)
{
	size_t	time;

	if (pthread_mutex_lock(&(*content)->death_protection) == 0)
	{
		if (!still_alive(content))
		{
			while (pthread_mutex_unlock(&(*content)->death_protection) != 0)
				;
			return (0);
		}
		time = timestamp_ms();
		(*content)->time_of_death = time + (*content)->args->die_time;
		printf("%ld %ld is eating\n", time, philo);
		while (pthread_mutex_unlock(&(*content)->death_protection) != 0)
			;
		ft_pause(content, duration);
	}
	return (1);
}

int	ph_sleep(t_ph **content, size_t philo, size_t duration)
{
	if (!still_alive(content))
		return (0);
	printf("%ld %ld is sleeping\n", timestamp_ms(), philo);
	ft_pause(content, duration);
	return (1);
}

int	ph_think(t_ph **content, size_t philo)
{
	if (!still_alive(content))
		return (0);
	printf("%ld %ld is thinking\n", timestamp_ms(), philo);
	return (1);
}

int	ph_died(t_ph **content, size_t philo)
{
	(*content)->died = 1;
	printf("%ld %ld died\n", timestamp_ms(), philo);
	return (1);
}
