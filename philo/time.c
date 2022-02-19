/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:42:55 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/19 17:40:14 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

size_t	timestamp_ms(void)
{
	t_timeval		tv;
	size_t			time;
	static size_t	simulation_start = 0;

	while (gettimeofday(&tv, NULL) == -1)
		;
	time = ((tv.tv_sec * 1000000) + tv.tv_usec) / 1000;
	if (simulation_start == 0)
		simulation_start = time;
	return (time - simulation_start);
}

int	ft_pause(t_ph **c, size_t duration)
{
	size_t	start;

	start = timestamp_ms();
	while (still_alive(c))
	{
		if (timestamp_ms() - start >= duration)
			return (1);
		usleep(100);
	}
	return (0);
}

int	still_alive(t_ph **c)
{
	int	res;

	res = 1;
	if (pthread_mutex_lock(&(*c)->args->simulation_mutex) == 0)
	{
		if ((*c)->args->simulation_off == 1)
			res = 0;
		pthread_mutex_unlock(&(*c)->args->simulation_mutex);
	}
	return (res);
}
