/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/09 20:59:17 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

/*
void	*runtime(void *arg)
{
	size_t i;

	i = 0;
	while (1)
	{
		if (!pthread_mutex_lock(&(((t_ph *)(arg))->fork_left))
			&& !pthread_mutex_lock(((pthread_mutex_t *)((t_ph *)(arg))->fork_right)))
		{
			ph_took_a_fork(((t_ph *)(arg))->number);
			ph_took_a_fork(((t_ph *)(arg))->number);
			ph_eat(((t_ph *)(arg))->number, ((t_ph *)(arg))->feed_ct, &arg);
			if (((t_ph *)(arg))->max_turns > 0)
			{
				if (++i == ((t_ph *)(arg))->max_turns)
				{
					return (NULL);
				}
			}
			pthread_mutex_unlock(&(((t_ph *)(arg))->fork_left));
			pthread_mutex_unlock(((pthread_mutex_t *)((t_ph *)(arg))->fork_right));
			// ph_releases_a_fork(((t_ph *)(arg))->number);
			// ph_releases_a_fork(((t_ph *)(arg))->number);			
			ph_sleep(((t_ph *)(arg))->number, ((t_ph *)(arg))->sleep_ct);
			ph_think(((t_ph *)(arg))->number);
		}
		else
		{
			ph_think(((t_ph *)(arg))->number);
		}
		// if mutex right && left are free
			// eat
			// sleep
		// else think
	}
	return (NULL);
}*/

void	*runtime(void *arg)
{
	t_timeval tv;

	if (((t_ph *)(arg))->number % 2 == 0)
		usleep(10);
	while (still_alive(((t_ph *)(arg))->timeout))
	{
		if (!pthread_mutex_lock(&(((t_ph *)(arg))->fork_left))
			&& !pthread_mutex_lock(((pthread_mutex_t *)((t_ph *)(arg))->fork_right)))
		{
			while (gettimeofday(&tv, NULL) == -1) ;
			((t_ph *)(arg))->timeout = (size_t)(tv.tv_usec + (long int)((t_ph *)(arg))->die_ct);
			if (ph_eat(((t_ph *)(arg))->number, ((t_ph *)(arg))->feed_ct))
			{
				while (pthread_mutex_unlock(&(((t_ph *)(arg))->fork_left)) != 0) ;
				while (pthread_mutex_unlock(((pthread_mutex_t *)((t_ph *)(arg))->fork_right)) != 0) ;
				if (still_alive(((t_ph *)(arg))->timeout))
					ph_sleep(((t_ph *)(arg))->number, ((t_ph *)(arg))->sleep_ct);
				if (still_alive(((t_ph *)(arg))->timeout))
					ph_think(((t_ph *)(arg))->number);
			}
		}
	}
	ph_died(((t_ph *)(arg))->number);
	return (NULL);
}