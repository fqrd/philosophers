/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 19:14:15 by fcaquard         ###   ########.fr       */
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

int	ph_eat(t_ph **arg, size_t philo, size_t duration)
{
	size_t time;

	time = timestamp_ms();
	printf("%ld %ld is eating\n", time, philo);
	// printf("%ld %ld is eating. death: %ld / duration: %ld\n", time, philo, (*arg)->time_of_death, duration);
	(*arg)->time_of_death = time + (* arg)->die_ct;
	ft_pause(arg, duration);
	return (1);
}

int	ph_sleep(t_ph **arg, size_t philo, size_t duration)
{
	printf("%ld %ld is sleeping\n", timestamp_ms(), philo);
	// printf("%ld %ld is sleeping / duration: %ld\n", timestamp_ms(), philo, duration);
	ft_pause(arg, duration);
	return (1);
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
