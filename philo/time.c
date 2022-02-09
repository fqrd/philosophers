/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:42:55 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 00:41:48 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

size_t	timestamp_ms(void)
{
	t_timeval tv;
	size_t time;

	while (gettimeofday(&tv, NULL) == -1) ;
	time = ((tv.tv_sec * 1000000) + tv.tv_usec) / 1000;
	return (time);
}

int	ft_pause(size_t duration)
{
	size_t	start;
	
	start = timestamp_ms();
	while (1)
	{
		if (timestamp_ms() - start >= duration)
			break ;
	}
	return (1);
}

int	still_alive(t_ph *arg, size_t count)
{
	if (timestamp_ms() >= arg->timeout)
		return (0);
	if (arg->max_turns != 0 && count >= arg->max_turns)
		return (0);
	return (1);
}
