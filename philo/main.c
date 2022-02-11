/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:30:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/11 19:57:00 by fcaquard         ###   ########.fr       */
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
	size_t i;
	
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

	// printf("killing sim\n");
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
	
	// printf("launching sim\n");
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

	if (argc < 5 || argc > 6 || !verifications(argc, argv))
	{
		printf("Invalid inputs\n");
		return (0);
	}

	// Gets argv[] datas and push them into a list
	args = init_args(argc, argv);
	if (!args)
	{
		printf("args init failed\n");
		return (0);
	}

	// LIST //
	// Generates a linked list of the number of philo provided
	// Returns first element
	list = generate_list(args->number);
	if (!list)
	{
		printf("generate_list failed\n");
		return (0);
	}
	// printf("List's been written down.\n");

	// CREATE PHILOS //
	// Assigns variables to each philo
	list = init_philos(args, list);
	if (!list)
	{
		printf("init philos failed");
		return (0);
	}
	// printf("philosophers gathered.\n");

	// CREATE THREADS //
	// Links each philo to a thread and each thread to runtime function
	list = init_pthreads(args, list);
	if (!list)
	{ 
		printf("init_ph failed\n");
		return (0);		
	}
	// printf("pthreads generated.\n");
	manage_threads(list);

	clear_loop_list(args->number, &list);
	free(args);
	return (1);
}
