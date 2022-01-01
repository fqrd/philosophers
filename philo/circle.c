/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:05:09 by fcaquard          #+#    #+#             */
/*   Updated: 2022/01/01 14:44:41 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	1[0] program
//	2[1] number_of_philosophers (also the number of forks)
//	3[2] time_to_die	(in ms, countdown to respect between each meals)
//	4[3] time_to_eat (time it takes to eat in ms, need 2 forks during that time)
//	5[4] time_to_sleep	(time it takes to sleep in ms)
//	6[5] number_of_times_each_philosophers_must_eat (optional, ends program when reached)

//	timestamp_in_ms	philo_number has taken a fork
//	timestamp_in_ms	philo_number is eating
//	timestamp_in_ms	philo_number is sleeping
//	timestamp_in_ms	philo_number is thinking
//	timestamp_in_ms	philo_number died

/*
memset
printf
malloc
free
write
usleep
gettimeofday
pthread_create
pthread_detach
pthread_join
pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock,
pthread_mutex_unlock
*/

static	void *live()
{
	ph_think(100);
	return (NULL);
}

static	t_list *init_pthreads(t_args *args, t_list *list)
{
	size_t	i;

	i = 0;
	while (i++ < args->philos)
	{
		list->content = malloc(sizeof(t_seat) * 1);
		if (!(list->content))
		{
			// TODO: should also destroy previous threads
			clear_loop_list(args, &list);
			return (NULL);
		}
		((t_seat *)(list->content))->number = i;
		if (pthread_create(&(((t_seat *)(list->content))->thread), NULL, &live, NULL))
		{
			// TODO: should also destroy previous threads
			clear_loop_list(args, &list);
			return (NULL);
		}
		ph_took_a_fork(((t_seat *)(list->content))->number);
		list = list->next;
	}
	return (list);
}

t_list	*generate_list(t_args *args)
{
	size_t	i;
	t_list	*list;
	t_list	*first;

	i = args->philos;
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

t_args	*init_args(int argc, char *argv[])
{
	t_args	*args;

	args = malloc(sizeof(t_args) * 1);
	if (!args)
		return (NULL);
	args->philos = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->feed_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		args->feed_max = ft_atoi(argv[5]);
	else
		args->feed_max = 0;
	return (args);
}

int	join(t_args *args, t_list *list)
{
	size_t	i;

	i = 0;
	while (i++ < args->philos)
	{
		if (pthread_join((((t_seat *)(list->content))->thread), NULL))
		{
			clear_loop_list(args, &list);
			return (0);
		}
		ph_died(((t_seat *)(list->content))->number);
		if (!list->next)
			break;
		list = list->next;
	}
	// ph_took_a_fork(args->philos);
	// ph_eat(args->philos);
	// ph_sleep(args->philos);
	// ph_think(args->philos);
	// ph_died(args->philos);
	return (1);	
}

int	main(int argc, char *argv[])
{
	t_args	*args;
	t_list *list;

	if (argc < 5 || argc > 6 || !verifications(argc, argv))
	{
		printf("Invalid inputs\n");
		return (0);
	}
	args = init_args(argc, argv);
	if (!args)
	{
		printf("args init failed\n");
		return (0);
	}

	// LIST //

	list = generate_list(args);
	if (!list)
	{
		printf("generate_list failed\n");
		return (0);
	}
	printf("List is written down.\n");

	// CREATE THREADS //

	list = init_pthreads(args, list);
	if (!list)
	{ 
		printf("init_seat failed\n");
		return (0);		
	}
	printf("pthreads generated.\n");

	// JOIN THREADS //

	if (!join(args, list))
	{
		printf("join failed\n");
		return (0);
	}
	printf("pthreads joined.\n");


	clear_loop_list(args, &list);
	free(args);
	return (1);
}
