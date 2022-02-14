/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:57:39 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/14 18:33:36 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_list	*generate_list(t_args **args)
{
	size_t	i;
	t_list	*list;
	t_list	*first;

	i = (*args)->number;
	list = NULL;
	while (i-- > 0)
	{
		list = init_list(&list);
		if (!list)
		{
			free(args);
			return (NULL);
		}
	}
	first = list_rewind(list);
	list->next = first;
	first->prev = list;
	return (first);
}
