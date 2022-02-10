/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 14:06:57 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*runtime(void *arg)
{
	size_t count;
	t_list *list;

	count = 0;
	list = (t_list *)(arg);
	if (((t_ph *)(list->content))->number % 2 == 0)
		ft_pause(&list->content, 1);
	while (((t_ph *)(list->content))->died == 0 && still_alive(&list->content) && is_complete(&list->content, count))
	{
		if (!pthread_mutex_lock(&(((t_ph *)(list->content))->fork_left))
			&& !pthread_mutex_lock(((pthread_mutex_t *)((t_ph *)(list->content))->fork_right)))
		{
			if (ph_eat(&list->content, ((t_ph *)(list->content))->number, ((t_ph *)(list->content))->feed_ct))
			{
				count++;
				while (pthread_mutex_unlock(&(((t_ph *)(list->content))->fork_left)) != 0) ;
				while (pthread_mutex_unlock(((pthread_mutex_t *)((t_ph *)(list->content))->fork_right)) != 0) ;
				if (((t_ph *)(list->content))->died == 0 && still_alive(&list->content) && is_complete(&list->content, count))
					ph_sleep(&list->content, ((t_ph *)(list->content))->number, ((t_ph *)(list->content))->sleep_ct);
				if (((t_ph *)(list->content))->died == 0 && still_alive(&list->content) && is_complete(&list->content, count))
					ph_think(((t_ph *)(list->content))->number);
			}
		}
		else // if one mutex has been locked in the if above unlock it
		{
			while (pthread_mutex_unlock(&(((t_ph *)(list->content))->fork_left)) != 0) ;
			while (pthread_mutex_unlock(((pthread_mutex_t *)((t_ph *)(list->content))->fork_right)) != 0) ;	
		}
	}
	if (((t_ph *)(list->content))->died == 1)
	{
		ph_died(((t_ph *)(list->content))->number);
	}
	else
		printf("death not defined in this scope\n");
	return (NULL);
}
