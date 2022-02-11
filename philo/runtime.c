/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/10 19:51:53 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	stop_sim(t_list **list)
{
	t_list  *start;

	start = *list;
	while (*list)
	{
		if (((t_ph *)(*list)->content)->sim_stop == 0)
		{
			((t_ph *)(*list)->content)->sim_stop = 1;
		}
		if ((*list)->next != start)
			*list = (*list)->next;
		else
			break ;
	}
}

int	await_forks(t_ph **content)
{
	int mutex_left;
	int mutex_right;

	while (1)
	{
		printf("%ld %ld is waiting...\n", timestamp_ms(), (*content)->number);
		mutex_left = pthread_mutex_lock(&((*content)->fork_left));
		mutex_right = pthread_mutex_lock(((pthread_mutex_t *)((*content)->fork_right)));
		if (mutex_left == 0 && mutex_right == 0)
		{
			if (still_alive(content))
				return (1);
			else
				return (0);
			// printf("%ld %ld wait is over...\n", timestamp_ms(), (*content)->number);
		}
	}
	return (0);
}

void	*runtime(void *arg)
{
	size_t	count;
	t_list	*list;
	t_ph	*content;

	count = 0;
	list = (t_list *)(arg);
	content = ((t_ph *)(list->content));

	if (content->number % 2 == 0)
		ft_pause(&content, 2);
	while (content->sim_stop == 0)
	{
		if (await_forks(&content))
		{
			ph_took_a_fork(content->number);
			ph_took_a_fork(content->number);
			if (ph_eat(&content, content->number, content->feed_ct))
			{
				count++;
				while (pthread_mutex_unlock(&(content->fork_left)) != 0) ;
				while (pthread_mutex_unlock(((pthread_mutex_t *)(content->fork_right))) != 0) ;
				if (content->sim_stop == 0 && still_alive(&content) && is_complete(&content, count))
					ph_sleep(&content, content->number, content->sleep_ct);
				if (content->sim_stop == 0 && still_alive(&content) && is_complete(&content, count))
					ph_think(content->number);
			}
		}
	}
	if (content->sim_stop == 1)
	{
		if (content->died == 1)
		{
			ph_died(content->number);
			stop_sim(&list);
		}
	}
	return (NULL);
}
