/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:57:39 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/12 17:03:06 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// only used up until the list is a loop 
static t_list	*list_rewind(t_list *list)
{
	while (list)
	{
		if (!list->prev)
			break ;
		list = list->prev;
	}
	return (list);
}

// uses list_rewind, so only if the list isn't a loop
static void	clear_list(t_list **list)
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

// clears the whole list on error
static t_list	*init_list(t_list **previous)
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

// returns NULL on error (list already cleared)
t_list	*generate_list(size_t i)
{
	t_list	*list;
	t_list	*first;

	list = NULL;
	while (i-- > 0)
	{
		list = init_list(&list);
		if (!list)
			return (NULL);
	}
	first = list_rewind(list);
	list->next = first;
	first->prev = list;
	return (first);
}
