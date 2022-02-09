/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:42:55 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/09 22:15:25 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

size_t	timestamp_ms(void)
{
	t_timeval tv;
	size_t time;

	while (gettimeofday(&tv, NULL) == -1) ;
	time = ((tv.tv_sec * 1000000) + tv.tv_usec) / 1000;
	// printf("time: %ld\n", time);
	return (time);
}


int	ft_timeout(size_t duration)
{
	size_t	start;
	
	start = timestamp_ms();
	while (1)
	{
		if (timestamp_ms() - start >= duration)
			break ;
		usleep(5);
	}
	return (1);
}

int	still_alive(size_t time_of_death)
{
	if (timestamp_ms() <= time_of_death)
		return (1);
	else
		return (0);
}