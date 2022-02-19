/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:12:18 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/19 15:27:50 by fcaquard         ###   ########.fr       */
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
	if (pthread_mutex_init(&args->write_mutex, NULL) != 0)
		return (NULL);
	return (args);
}

static int	populate_philo(t_args **args, t_ph *content)
{
	content->args = *args;
	content->died = 0;
	content->time_of_death = 0;
	content->sim_stop = 0;
	content->all_ready = 0;
	if (pthread_mutex_init(&content->fork_left, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&content->death_protection, NULL) != 0)
		return (0);
	return (1);
}

static t_list	*init_philos(t_args **args, t_list *list)
{
	size_t	i;

	i = 0;
	while (i++ < (*args)->number)
	{
		list->content = malloc(sizeof(t_ph) * 1);
		if (!list->content)
		{
			clear(&list, args);
			return (NULL);
		}
		((t_ph *)(list->content))->number = i;
		if (!populate_philo(args, (t_ph *)(list->content)))
		{
			clear(&list, args);
			return (NULL);
		}
		list = list->next;
	}
	return (list);
}

static int	verifications(int argc, char *argv[])
{
	size_t	i;
	size_t	j;

	i = argc;
	while (i-- > 1)
	{
		j = 0;
		while (argv[i] && argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (0);
			j++;
		}
	}
	return (1);
}

int	preparation(int argc, char *argv[], t_args **args, t_list **list)
{
	if (argc < 5 || argc > 6 || !verifications(argc, argv))
	{
		printf("Error: Invalid input.\n");
		return (0);
	}
	*args = init_args(argc, argv);
	if (!(*args))
	{
		printf("Error: Arguments list generation failed. (malloc)\n");
		return (0);
	}
	*list = generate_list(args);
	if (!(*list))
	{
		printf("Error: Threads list generation failed. (malloc)\n");
		return (0);
	}
	*list = init_philos(args, *list);
	if (!(*list))
	{
		printf("Error: Philosophers initialization failed. (malloc)");
		return (0);
	}
	return (1);
}
