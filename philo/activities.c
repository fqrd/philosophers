/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 14:26:38 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	timestamp_in_ms	philo_number has taken a fork
//	timestamp_in_ms	philo_number is eating
//	timestamp_in_ms	philo_number is sleeping
//	timestamp_in_ms	philo_number is thinking
//	timestamp_in_ms	philo_number died

int	ph_took_a_fork(size_t philo)
{
	printf("%ld %ld has taken a fork\n", timestamp_ms(), philo);
	return (1);
}

int	ph_eat(void **arg, size_t philo, size_t duration)
{
	printf("%ld %ld is eating\n", timestamp_ms(), philo);
	((t_ph *)(*arg))->time_of_death = timestamp_ms() + ((t_ph *)(* arg))->die_ct;
	return (ft_pause(arg, duration));
}

int	ph_sleep(void **arg, size_t philo, size_t duration)
{
	printf("%ld %ld is sleeping\n", timestamp_ms(), philo);
	return (ft_pause(arg, duration));
}

int	ph_think(size_t philo)
{
	printf("%ld %ld is thinking\n", timestamp_ms(), philo);
	return (1);
}

int	ph_died(size_t philo)
{
	printf("%ld %ld died\n", timestamp_ms(), philo);
	return (1);
}
