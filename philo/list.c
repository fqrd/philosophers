/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:57:39 by fcaquard          #+#    #+#             */
/*   Updated: 2022/01/01 14:49:46 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*list_rewind(t_list *list)
{
	while (list)
	{
		if(!list->prev)
			break ;
		list = list->prev;
	}
	return (list);
}

void	clear_list(t_list **list)
{
	t_list	*tmp;

	*list = list_rewind(*list);
	while (*list)
	{
		if (!(*list)->next)
		{
			if ((*list)->content)
				free((*list)->content);
			free(*list);
			break ;
		}
		tmp = (*list)->next;
		if ((*list)->content)
			free((*list)->content);
		free(*list);
		*list = tmp;
	}
}

void	clear_loop_list(size_t size, t_list **list)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	while (i++ < size)
	{
		if (!(*list)->next)
		{
			if ((*list)->content)
				free((*list)->content);
			free(*list);
			break ;
		}
		tmp = (*list)->next;
		if ((*list)->content)
			free((*list)->content);
		free(*list);
		*list = tmp;
	}
}

t_list	*init_list(t_list **previous)
{
	t_list	*list;

	list = malloc(sizeof(t_list) * 1);
	if (!list)
	{
		clear_list(previous);
		return (NULL);
	}
	list->prev = NULL;
	list->next = NULL;
	if (*previous)
	{
		list->prev = *previous;
		(*previous)->next = list;
	}
	return (list);
}
