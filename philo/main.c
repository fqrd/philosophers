/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:30:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/12 18:19:08 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_list	*init_pthreads(t_args *args, t_list *list)
{
	size_t	i;
	
	i = 0;
	while (i++ < args->number)
	{
		((t_ph *)(list->content))->time_of_death = ((t_ph *)(list->content))->die_ct;
		((t_ph *)(list->content))->fork_right = &(((t_ph *)(list->prev->content))->fork_left);
		if (pthread_create(&(((t_ph *)(list->content))->thread), NULL, &runtime, list))
		{
			// should clear mutex and threads !
			// pthread_mutex_destroy(&mutex);
			printf("Error init_pthread\n");
			clear_loop_list(args->number, &list);
			return (NULL);
		}
		list = list->next;
	}
	return (list);
}

static int	kill_simulation(t_list *list)
{
	t_list *start;

	start = list;
	((t_ph *)(list->content))->sim_stop = 1;
	list = list->next;
	while (list != start)
	{
		((t_ph *)(list->content))->sim_stop = 1;
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

static int 	manage_threads(t_list *list)
{
	size_t time;
	t_ph *content;

	launch_sim(list);
	while (1)
	{
		time = timestamp_ms();
		content = ((t_ph *)(list->content));

		if (content->time_of_death < time)
		{
			if (content->sim_stop == 0)
			{
				printf("%ld %ld/%ld\n", content->number, time, content->time_of_death);
				ph_died(&content, content->number);
				kill_simulation(list);
			}
			break ;
		}
		list = list->next;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_args	*args;
	t_list *list;

	if (!preparation(argc, argv, &args, &list))
		return (0);

	list = init_pthreads(args, list);
	if (!list)
	{ 
		printf("init_ph failed\n");
		return (0);		
	}

	manage_threads(list);

	clear_loop_list(args->number, &list);
	free(args);
	return (1);
}
