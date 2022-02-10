/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:42:55 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 14:28:43 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

size_t	timestamp_ms()
{
	t_timeval		tv;
	size_t			time;
	static size_t	simulation_start = 0;

	while (gettimeofday(&tv, NULL) == -1) ;
	time = ((tv.tv_sec * 1000000) + tv.tv_usec) / 1000;
	if (simulation_start == 0)
		simulation_start = time;
	return (time - simulation_start);
}

int	ft_pause(void **arg, size_t duration)
{
	size_t	start;
	
	start = timestamp_ms();
	while (1)
	{
		if (!still_alive(arg)
			|| timestamp_ms() - start >= duration)
			break ;
	}
	return (1);
}

int	still_alive(void **arg)
{
	t_ph *content;

	content = (t_ph *)(*arg);
	
	// DEBUG
	size_t time = timestamp_ms();
	if (time > content->time_of_death)
	{
		printf("DIED: %ld -> %ld @ %ld\n", content->number, content->time_of_death, time);
		content->died = 1;
		return (0);
	}
	return (1);
}

int	is_complete(void **arg, size_t count)
{
	t_ph *content;

	content = (t_ph *)(*arg);
	if (content->max_turns != 0 && count >= content->max_turns)
		return (0);
	return (1);	
}
