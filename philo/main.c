/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:30:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/14 11:30:35 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_list	*init_pthreads(t_args **args, t_list *list)
{
	size_t	i;
	t_ph	*content;

	i = 0;
	while (i++ < (*args)->number)
	{
		content = (t_ph *)(list->content);
		content->time_of_death = content->die_ct;
		content->fork_right = &(((t_ph *)(list->prev->content))->fork_left);
		if (pthread_create(&(content->thread), NULL, &runtime, list))
		{
			// should clear mutex and threads !
			// pthread_mutex_destroy(&mutex);
			printf("Error init_pthread\n");
			clear_loop_list((*args)->number, &list, 1);
			free(args);
			return (NULL);
		}
		list = list->next;
	}
	return (list);
}

static int	kill_simulation(t_list *list)
{
	t_list	*start;
	t_ph *	content;

	start = list;
	((t_ph *)(list->content))->sim_stop = 1;
	list = list->next;
	while (list != start)
	{
		content = (t_ph *)(list->content);
		content->sim_stop = 1;
		list = list->next;
	}
	return (1);
}

static int	launch_sim(t_list *list)
{
	t_list	*start;

	start = list;
	((t_ph *)(list->content))->all_ready = 1;
	list = list->next;
	while (list != start)
	{
		((t_ph *)(list->content))->all_ready = 1;
		list = list->next;
	}
	return (1);
}

static int	manage_threads(t_list *list)
{
	t_ph	*content;

	launch_sim(list);
	while (1)
	{
		content = ((t_ph *)(list->content));
		if (content->time_of_death < timestamp_ms())
		{
			if (!pthread_mutex_lock(&(content->death_protection)))
			{
				printf("death: mutex locked\n");
				if (content->sim_stop == 0)
				{
					ph_died(&content, content->number);
					kill_simulation(list);
				}
			}
			pthread_mutex_unlock(&(content->death_protection));
			printf("death: mutex unlocked\n");
			break ;
		}
		list = list->next;
	}
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
	clear_loop_list(args->number, &list, 1);
	free(args);
	return (1);
}
