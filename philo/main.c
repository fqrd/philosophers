/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:30:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/20 11:31:21 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_list	*init_pthreads(t_args **args, t_list *list)
{
	t_ph	*content;
	t_list	*start;

	start = NULL;
	while (list != start)
	{
		if (!start)
			start = list;
		content = (t_ph *)(list->content);
		content->time_of_death = content->args->die_time;
		if (list->prev != list)
			content->fork_right = &(((t_ph *)(list->prev->content))->fork_left);
		else
			content->fork_right = NULL;
		if (pthread_create(&(content->thread), NULL, &runtime, list) != 0)
		{
			clear(&list, args);
			return (NULL);
		}
		list = list->next;
	}
	return (list);
}

static int	toggle_sim(t_list *list, int on)
{
	t_list	*start;

	start = NULL;
	while (list != start)
	{
		if (!start)
			start = list;
		if (on)
			((t_ph *)(list->content))->thread_active = 1;
		else
			((t_ph *)(list->content))->thread_active = 0;
		list = list->next;
	}
	return (1);
}

static	int	is_running(t_ph *content)
{
	int	res;

	res = 1;
	if (content->time_of_death < timestamp_ms())
	{
		if (pthread_mutex_lock(&content->death_protection) == 0)
		{
			if (content->thread_active == 1)
				ph_died(&content, content->number);
			pthread_mutex_unlock(&(content->death_protection));
		}
		res = 0;
	}
	else if (pthread_mutex_lock(&content->args->simulation_mutex) == 0)
	{
		if (content->args->simulation_off == 1)
			res = 0;
		pthread_mutex_unlock(&content->args->simulation_mutex);
	}
	return (res);
}

static int	manage_threads(t_list *list)
{
	toggle_sim(list, 1);
	while (1)
	{
		if (!is_running((t_ph *)list->content))
			break ;
		list = list->next;
	}
	toggle_sim(list, 0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_args	*args;
	t_list	*list;

	args = NULL;
	if (!preparation(argc, argv, &args, &list))
		return (0);
	list = init_pthreads(&args, list);
	if (!list)
		return (0);
	manage_threads(list);
	clear(&list, &args);
	return (1);
}
