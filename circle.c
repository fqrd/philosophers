/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:05:09 by fcaquard          #+#    #+#             */
/*   Updated: 2021/12/21 19:30:15 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	1[0] program
//	2[1] number_of_philosophers (also the number of forks)
//	3[2] time_to_die	(in ms, countdown to respect between each meals)
//	4[3] time_to_eat (time it takes to eat in ms, need 2 forks during that time)
//	5[4] time_to_sleep	(time it takes to sleep in ms)
//	6[5] number_of_times_each_philosophers_must_eat (optional, ends program when reached)

//	timestamp_in_ms	philo_number has taken a fork
//	timestamp_in_ms	philo_number is eating
//	timestamp_in_ms	philo_number is sleeping
//	timestamp_in_ms	philo_number is thinking
//	timestamp_in_ms	philo_number died

void	*sit(int n, int countdown, int feeding, int sleeping, int tours)
{
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int tours;

	tours = -1;
	if (argc < 5 || argc > 6)
		return (0);
	while (argc-- > 1)
	{
		if (!ft_atoi(argv[argc]))
			return (0);
	}
	if (argc == 6)
		tours == argv[5];
	sit(argv[1], argv[2], argv[3], argv[4], tours);
	return (0);
}