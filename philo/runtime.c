/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 00:33:42 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*runtime(void *arg)
{
	size_t count;
	t_list *list;

	count = 0;
	list = 	(t_list *)(arg);
	if (((t_ph *)(list->content))->number % 2 == 0)
		ft_pause(((t_ph *)(list->content))->feed_ct / 10);
	while (still_alive(((t_ph *)(list->content)), count) 
		&& (((t_ph *)(list->content))->max_turns == 0 || count < ((t_ph *)(list->content))->max_turns))
	{
		if (!pthread_mutex_lock(&(((t_ph *)(list->content))->fork_left))
			&& !pthread_mutex_lock(((pthread_mutex_t *)((t_ph *)(list->content))->fork_right)))
		{
			((t_ph *)(list->content))->timeout = timestamp_ms() + ((t_ph *)(list->content))->die_ct;
			if (ph_eat(((t_ph *)(list->content))->number, ((t_ph *)(list->content))->feed_ct))
			{
				count++;
				while (pthread_mutex_unlock(&(((t_ph *)(list->content))->fork_left)) != 0) ;
				while (pthread_mutex_unlock(((pthread_mutex_t *)((t_ph *)(list->content))->fork_right)) != 0) ;
				if (still_alive(((t_ph *)(list->content)), count))
					ph_sleep(((t_ph *)(list->content))->number, ((t_ph *)(list->content))->sleep_ct);
				if (still_alive(((t_ph *)(list->content)), count))
					ph_think(((t_ph *)(list->content))->number);
			}
		}
		else // if one mutex has been locked in the if above unlock it
		{
			while (pthread_mutex_unlock(&(((t_ph *)(list->content))->fork_left)) != 0) ;
			while (pthread_mutex_unlock(((pthread_mutex_t *)((t_ph *)(list->content))->fork_right)) != 0) ;	
		}
	}
	ph_died(((t_ph *)(list->content))->number);
	return (NULL);
}
