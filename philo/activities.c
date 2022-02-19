/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/19 17:57:36 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_took_a_fork(t_ph **c, size_t philo)
{
	if (pthread_mutex_lock(&(*c)->args->write_mutex) == 0)
	{
		if (still_alive(c) == 1)
		{
			printf("%ld %ld has taken a fork\n", timestamp_ms(), philo);
			pthread_mutex_unlock(&(*c)->args->write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&(*c)->args->write_mutex);
	}
	return (0);
}

int	ph_eat(t_ph **c, size_t philo, size_t duration)
{
	if (pthread_mutex_lock(&(*c)->death_protection) == 0)
	{
		if (pthread_mutex_lock(&(*c)->args->write_mutex) == 0)
		{
			if (still_alive(c) == 1)
			{
				printf("%ld %ld is eating\n", timestamp_ms(), philo);
				(*c)->time_of_death = timestamp_ms() + (*c)->args->die_time;
				pthread_mutex_unlock(&(*c)->args->write_mutex);
				pthread_mutex_unlock(&(*c)->death_protection);
				ft_pause(c, duration);
				return (1);
			}
			pthread_mutex_unlock(&(*c)->args->write_mutex);
		}
		pthread_mutex_unlock(&(*c)->death_protection);
	}
	return (0);
}

int	ph_sleep(t_ph **c, size_t philo, size_t duration)
{
	if (pthread_mutex_lock(&(*c)->args->write_mutex) == 0)
	{
		if (still_alive(c) == 1)
		{
			printf("%ld %ld is sleeping\n", timestamp_ms(), philo);
			pthread_mutex_unlock(&(*c)->args->write_mutex);
			ft_pause(c, duration);
			return (1);
		}	
		pthread_mutex_unlock(&(*c)->args->write_mutex);
	}
	return (0);
}

int	ph_think(t_ph **c, size_t philo)
{
	if (pthread_mutex_lock(&(*c)->args->write_mutex) == 0)
	{
		if (still_alive(c) == 1)
		{
			printf("%ld %ld is thinking\n", timestamp_ms(), philo);
			pthread_mutex_unlock(&(*c)->args->write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&(*c)->args->write_mutex);
	}
	return (0);
}

int	ph_died(t_ph **c, size_t philo)
{
	if (pthread_mutex_lock(&(*c)->args->write_mutex) == 0)
	{
		if (still_alive(c) == 1)
		{
			if (pthread_mutex_lock(&(*c)->args->simulation_mutex) == 0)
			{
				(*c)->args->simulation_off = 1;
				pthread_mutex_unlock(&(*c)->args->simulation_mutex);
			}
			printf("%ld %ld died\n", timestamp_ms(), philo);
		}
		pthread_mutex_unlock(&(*c)->args->write_mutex);
		return (1);
	}
	return (0);
}
