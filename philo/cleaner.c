/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:10:39 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/14 16:01:12 by fcaquard         ###   ########.fr       */
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
		if (pthread_join(content->thread, NULL) != 0)
		{
			printf("Error terminating thread\n");
			return (0);
		}
		else
		{
			printf("%ld thread terminated\n", content->number);
		}
		*list = (*list)->next;
	}
	printf("All threads terminated\n");
	return (1);	
}

static int	unlock_mutexes(t_list **list)
{
	t_ph	*content;
	t_list	*start;

	start = NULL;
	while (*list != start)
	{
		if (!start)
			start = *list;
		content = (t_ph *)(*list)->content;
		while (pthread_mutex_unlock(&content->death_protection) != 0)
			;
		while (pthread_mutex_unlock(&content->fork_left) != 0)
			;
		while (pthread_mutex_unlock((pthread_mutex_t *)content->fork_right) != 0)
			;
		*list = (*list)->next;
		printf("%ld Mutexes unlocked\n", content->number);
	}
	printf("All Mutexes unlocked\n");
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
		// if (pthread_mutex_destroy(&(content->death_protection)) != 0)
		// {
		// 	printf("%ld Error destroying death_protection mutex\n", content->number);
		// 	// return (0);
		// }
		// else
		// {
		// 	printf("%ld destroy successfull\n", content->number);
		// }			
		if (pthread_mutex_destroy(&(content->fork_left)) != 0)
		{
			printf("%ld Error destroying fork_left mutex\n", content->number);
			// return (0);
		}
		// if (pthread_mutex_destroy((pthread_mutex_t *)(content->fork_right)) != 0)
		// {
		// 	printf("%ld Error destroying fork_right mutex\n", content->number);
		// 	// return (0);
		// }
		*list = (*list)->next;
	}
	printf("mutexes destroyed\n");
	return (1);
}

static int	clear_loop_list(t_list **list)
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
	printf("unlock_mutexes\n");
	if (!unlock_mutexes(list))
		return (0);
	printf("destroy_mutexes\n");
	if (!destroy_mutexes(list))
		return (0);
	printf("clear loop list\n");
	if (!clear_loop_list(list))
		return (0);
	printf("free args\n");
	free(*args);
	return (1);
}
