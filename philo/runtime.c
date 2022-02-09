/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/09 22:33:29 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*runtime(void *arg)
{
	size_t count;

	count = 0;
	if (((t_ph *)(arg))->number % 2 == 0)
		usleep(1);
	while (1)
	{
		if (!pthread_mutex_lock(&(((t_ph *)(arg))->fork_left))
			&& !pthread_mutex_lock(((pthread_mutex_t *)((t_ph *)(arg))->fork_right)))
		{
			((t_ph *)(arg))->timeout = timestamp_ms() + ((t_ph *)(arg))->die_ct;
			if (ph_eat(((t_ph *)(arg))->number, ((t_ph *)(arg))->feed_ct))
			{
				count++;
				while (pthread_mutex_unlock(&(((t_ph *)(arg))->fork_left)) != 0) ;
				while (pthread_mutex_unlock(((pthread_mutex_t *)((t_ph *)(arg))->fork_right)) != 0) ;
				if (still_alive(((t_ph *)(arg))->timeout))
					ph_sleep(((t_ph *)(arg))->number, ((t_ph *)(arg))->sleep_ct);
				if (still_alive(((t_ph *)(arg))->timeout))
					ph_think(((t_ph *)(arg))->number);
			}
		}
		else // if one mutex has been locked unlock it
		{
			while (pthread_mutex_unlock(&(((t_ph *)(arg))->fork_left)) != 0) ;
			while (pthread_mutex_unlock(((pthread_mutex_t *)((t_ph *)(arg))->fork_right)) != 0) ;	
		}
	}
	ph_died(((t_ph *)(arg))->number);
	return (NULL);
}
