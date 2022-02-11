/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/11 20:03:56 by fcaquard         ###   ########.fr       */
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

void	*runtime(void *arg)
{
	size_t	count;
	t_list	*list;
	t_ph	*content;

	count = 0;
	list = (t_list *)(arg);
	content = ((t_ph *)(list->content));

	while (content->all_ready == 0) ;
	if (content->number % 2 == 0)
		ft_pause(&content, 50);
	while (content->sim_stop == 0)
	{
		if (!pthread_mutex_lock(&(content->fork_left))
			&& !pthread_mutex_lock(((pthread_mutex_t *)(content->fork_right)))
				&& still_alive(&content))
		{
			ph_took_a_fork(&content, content->number);
			ph_took_a_fork(&content, content->number);
			if (ph_eat(&content, content->number, content->feed_ct))
			{
				while (pthread_mutex_unlock(&(content->fork_left)) != 0) ;
				while (pthread_mutex_unlock((pthread_mutex_t *)(content->fork_right)) != 0) ;
				if (content->max_turns != 0 && ++count >= content->max_turns)
				{
					content->sim_stop = 1;
					printf("max turns attained\n");
					break ;
				}
				ph_sleep(&content, content->number, content->sleep_ct);
				ph_think(&content, content->number);
			}
		}
	}
	return (NULL);
}
