/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/14 15:08:16 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	eat_sleep_work(t_ph *arg, size_t *count)
{
	if (ph_eat(&arg, arg->number, arg->feed_ct))
	{
		while (pthread_mutex_unlock(&(arg->fork_left)) != 0)
			;
		while (pthread_mutex_unlock((pthread_mutex_t *)(arg->fork_right)) != 0)
			;
		if (arg->max_turns != 0 && ++(*count) >= arg->max_turns)
		{
			arg->sim_stop = 1;
			return (0);
		}
		ph_sleep(&arg, arg->number, arg->sleep_ct);
		ph_think(&arg, arg->number);
	}
	return (1);
}

void	*runtime(void *list)
{
	size_t	count;
	t_ph	*content;

	count = 0;
	content = ((t_ph *)(((t_list *)(list))->content));
	while (content->all_ready == 0)
		;
	if (content->number % 2 == 0)
		ft_pause(&content, 50);
	while (content->sim_stop == 0)
	{
		if (pthread_mutex_lock(&(content->fork_left)) == 0)
			ph_took_a_fork(&content, content->number);
		if (pthread_mutex_lock(((pthread_mutex_t *)(content->fork_right))) == 0)
			ph_took_a_fork(&content, content->number);
		if (!eat_sleep_work(content, &count))
			break ;
	}
	return (NULL);
}
