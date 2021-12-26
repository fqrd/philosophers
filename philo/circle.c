/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:05:09 by fcaquard          #+#    #+#             */
/*   Updated: 2021/12/26 18:23:15 by fcaquard         ###   ########.fr       */
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

t_args	*init_args(void)
{
	t_args	*args;

	args = malloc(sizeof(t_args) * 1);
	if (!args)
		return (NULL);
	return (args);
}

int	check_digits(char *inputs)
{
	(void)inputs;
	return (1);
}

int	sit(t_args *args)
{
	ph_took_a_fork(args->philos);
	ph_eat(args->philos);
	ph_sleep(args->philos);
	ph_think(args->philos);
	ph_died(args->philos);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_args	*args;

	if (argc < 5 || argc > 6)
		return (0);
	while (argc-- > 1)
	{
		if (!check_digits(argv[argc]))
			return (0);
	}
	args = init_args();
	if (!args)
		return (0);
	args->philos = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->feed_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		args->feed_max = ft_atoi(argv[5]);
	else
		args->feed_max = 0;
	sit(args);
	free(args);
	return (1);
}
