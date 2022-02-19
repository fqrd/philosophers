/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/19 15:44:53 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_took_a_fork(t_ph **content, size_t philo)
{
	if (pthread_mutex_lock(&(*content)->args->write_mutex) == 0)
	{
		if (still_alive(content))
		{
			printf("%ld %ld has taken a fork\n", timestamp_ms(), philo);
			pthread_mutex_unlock(&(*content)->args->write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&(*content)->args->write_mutex);
	}
	return (0);
}

int	ph_eat(t_ph **content, size_t philo, size_t duration)
{
	if (pthread_mutex_lock(&(*content)->death_protection) == 0)
	{
		if (still_alive(content))
	 	{
			if (pthread_mutex_lock(&(*content)->args->write_mutex) == 0)
			{
				printf("%ld %ld is eating\n", timestamp_ms(), philo);
				(*content)->time_of_death = timestamp_ms() + (*content)->args->die_time;
				pthread_mutex_unlock(&(*content)->args->write_mutex);
				pthread_mutex_unlock(&(*content)->death_protection);
				ft_pause(content, duration);
				return (1);
			}
		}
		pthread_mutex_unlock(&(*content)->death_protection);
	}
	return (0);
}

int	ph_sleep(t_ph **content, size_t philo, size_t duration)
{
	if (pthread_mutex_lock(&(*content)->args->write_mutex) == 0)
	{
		if (still_alive(content))
		{
			printf("%ld %ld is sleeping\n", timestamp_ms(), philo);
			pthread_mutex_unlock(&(*content)->args->write_mutex);
			ft_pause(content, duration);
			return (1);
		}	
		pthread_mutex_unlock(&(*content)->args->write_mutex);
	}
	return (0);
}

int	ph_think(t_ph **content, size_t philo)
{
	if (pthread_mutex_lock(&(*content)->args->write_mutex) == 0)
	{
		if (still_alive(content))
		{
			printf("%ld %ld is thinking\n", timestamp_ms(), philo);
			pthread_mutex_unlock(&(*content)->args->write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&(*content)->args->write_mutex);
	}
	return (0);
}

int	ph_died(t_ph **content, size_t philo)
{
	if (pthread_mutex_lock(&(*content)->args->write_mutex) == 0)
	{
		printf("%ld %ld died\n", timestamp_ms(), philo);
		(*content)->died = 1;
		pthread_mutex_unlock(&(*content)->args->write_mutex);
	}
	return (1);
}
