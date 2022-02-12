/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/12 11:48:25 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	timestamp_in_ms	philo_number has taken a fork
//	timestamp_in_ms	philo_number is eating
//	timestamp_in_ms	philo_number is sleeping
//	timestamp_in_ms	philo_number is thinking
//	timestamp_in_ms	philo_number died


/*
int	ph_took_a_fork(t_ph **arg, size_t philo)
{
	if (!still_alive(arg))
		return (0);
	printf("%ld %ld has taken a fork\n", timestamp_ms(), philo);
	return (1);
}

int	ph_eat(t_ph **arg, size_t philo, size_t duration)
{
	// size_t time;

	// time = timestamp_ms();
	if (!still_alive(arg))
		return (0);
	(*arg)->eats = 1;
	(*arg)->time_of_death = timestamp_ms() + (* arg)->die_ct;
	printf("%ld %ld is eating\n", timestamp_ms(), philo);
	ft_pause(arg, duration);
	(*arg)->eats = 0;
	return (1);
}

int	ph_sleep(t_ph **arg, size_t philo, size_t duration)
{
	if (!still_alive(arg))
		return (0);
	(*arg)->sleeps = 1;
	printf("%ld %ld is sleeping\n", timestamp_ms(), philo);
	ft_pause(arg, duration);
	(*arg)->sleeps = 0;
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
	// if (!still_alive(arg))
	// 	return (0);
	(*arg)->died = 1;
	printf("%ld %ld died\n", timestamp_ms(), philo);
	return (1);
}
*/

int	ph_took_a_fork(t_ph **arg, size_t philo)
{
	if (!still_alive(arg))
		return (0);
	if (!build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), "has taken a fork"))
		return (0);
	return (1);
}

int	ph_eat(t_ph **arg, size_t philo, size_t duration)
{
	if (!still_alive(arg))
		return (0);
	if (!build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), "is eating"))
		return (0);
	((t_ph *)(*arg))->time_of_death = timestamp_ms() + ((t_ph *)(* arg))->die_ct;
	return (ft_pause(arg, duration));
}

int	ph_sleep(t_ph **arg, size_t philo, size_t duration)
{
	if (!still_alive(arg))
		return (0);
	if (!build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), "is sleeping"))
		return (0);
	return (ft_pause(arg, duration));
}

int	ph_think(t_ph **arg, size_t philo)
{
	if (!still_alive(arg))
		return (0);
	if (!build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), "is thinking"))
		return (0);
	return (1);
}

int	ph_died(t_ph **arg, size_t philo)
{
	if (!build_str(atoi_size_t(timestamp_ms()), ft_itoa(philo), "died"))
		return (0);
	(*arg)->died = 1;
	return (1);
}