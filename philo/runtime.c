/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 14:27:54 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*runtime(void *arg)
{
	size_t	count;
	t_list	*list;
	t_ph	*content;

	count = 0;
	list = (t_list *)(arg);
	content = ((t_ph *)(list->content));
	if (content->number % 2 == 0)
		ft_pause(&list->content, 1);
	while (content->died == 0 && still_alive(&list->content) && is_complete(&list->content, count))
	{
		if (!pthread_mutex_lock(&(content->fork_left))
			&& !pthread_mutex_lock(((pthread_mutex_t *)(content->fork_right))))
		{
			ph_took_a_fork(content->number);
			ph_took_a_fork(content->number);
			if (ph_eat(&list->content, content->number, content->feed_ct))
			{
				count++;
				while (pthread_mutex_unlock(&(content->fork_left)) != 0) ;
				while (pthread_mutex_unlock(((pthread_mutex_t *)(content->fork_right))) != 0) ;
				if (content->died == 0 && still_alive(&list->content) && is_complete(&list->content, count))
					ph_sleep(&list->content, content->number, content->sleep_ct);
				if (content->died == 0 && still_alive(&list->content) && is_complete(&list->content, count))
					ph_think(content->number);
			}
		}
		else // if one mutex has been locked in the if above unlock it
		{
			while (pthread_mutex_unlock(&(content->fork_left)) != 0) ;
			while (pthread_mutex_unlock(((pthread_mutex_t *)(content->fork_right))) != 0) ;	
		}
	}
	if (content->died == 1)
		ph_died(content->number);
	return (NULL);
}
