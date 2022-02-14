/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:10:39 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/14 18:32:36 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	terminate_threads(t_list **list)
{
	t_ph	*content;
	t_list	*start;

	start = NULL;
	while (*list != start)
	{
		if (!start)
			start = *list;
		content = (t_ph *)(*list)->content;
		pthread_join(content->thread, NULL);
		*list = (*list)->next;
	}
	return (1);
}

static int	destroy_mutexes(t_list **list)
{
	t_ph	*content;
	t_list	*start;

	start = NULL;
	while (*list != start)
	{
		if (!start)
			start = *list;
		content = (t_ph *)(*list)->content;
		if ((pthread_mutex_t *)&(content->death_protection) != NULL)
		{
			if (pthread_mutex_destroy(&(content->death_protection)) != 0)
				return (0);
		}
		if ((pthread_mutex_t *)&(content->fork_left) != NULL)
		{
			if (pthread_mutex_destroy(&(content->fork_left)) != 0)
				return (0);
		}
		*list = (*list)->next;
	}
	return (1);
}

static int	clear_philosophers(t_list **list)
{
	t_list	*start;
	t_list	*tmp;

	start = NULL;
	while (*list != start)
	{
		if (!start)
			start = *list;
		tmp = (*list)->next;
		if ((*list)->content)
			free((*list)->content);
		free(*list);
		*list = tmp;
	}
	return (1);
}

int	clear(t_list **list, t_args **args)
{
	if (!terminate_threads(list))
		return (0);
	if (!destroy_mutexes(list))
		return (0);
	if (!clear_philosophers(list))
		return (0);
	free(*args);
	return (1);
}
