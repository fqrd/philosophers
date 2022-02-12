/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:12:18 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/12 18:20:28 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static t_args	*init_args(int argc, char *argv[])
{
	t_args	*args;

	args = malloc(sizeof(t_args) * 1);
	if (!args)
		return (NULL);
	args->number = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->feed_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		args->feed_max = ft_atoi(argv[5]);
	return (args);
}

static t_list	*init_philos(t_args *args, t_list *list)
{
	size_t	i;

	i = 0;
	while (i++ < args->number)
	{
		list->content = malloc(sizeof(t_ph) * 1);
		if (!list->content)
		{
			clear_loop_list(args->number, &list);
			return (NULL);
		}
		((t_ph *)(list->content))->number = i;
		((t_ph *)(list->content))->die_ct = args->die_time;
		((t_ph *)(list->content))->feed_ct = args->feed_time;
		((t_ph *)(list->content))->sleep_ct = args->sleep_time;
		((t_ph *)(list->content))->max_turns = args->feed_max;
		((t_ph *)(list->content))->died = 0;
		((t_ph *)(list->content))->time_of_death = 0;
		((t_ph *)(list->content))->sim_stop = 0;
		((t_ph *)(list->content))->all_ready = 0;
		pthread_mutex_init(&((t_ph *)(list->content))->fork_left, NULL);
		list = list->next;
	}
	return (list);
}

int	preparation(int argc, char *argv[], t_args **args, t_list **list)
{
	if (argc < 5 || argc > 6 || !verifications(argc, argv))
	{
		printf("Invalid inputs\n");
		return (0);
	}
	*args = init_args(argc, argv);
	if (!(*args))
	{
		printf("args init failed\n");
		return (0);
	}
	*list = generate_list((*args)->number);
	if (!(*list))
	{
		printf("generate_list failed\n");
		return (0);
	}
	*list = init_philos(*args, *list);
	if (!(*list))
	{
		printf("init philos failed");
		return (0);
	}
	return (1);
}