/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/14 18:12:09 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	eat_sleep_work(t_ph *content, size_t *count)
{
	int	res;

	res = ph_eat(&content, content->number, content->feed_ct);
	while (pthread_mutex_unlock(&(content->fork_left)) != 0)
		;
	while (pthread_mutex_unlock((pthread_mutex_t *)(content->fork_right)) != 0)
		;
	if (!res)
		return (0);
	if (content->max_turns != 0 && ++(*count) >= content->max_turns)
	{
		content->sim_stop = 1;
		return (0);
	}
	ph_sleep(&content, content->number, content->sleep_ct);
	ph_think(&content, content->number);
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
		if (content->fork_right == NULL)
		{
			while (pthread_mutex_unlock(&content->fork_left))
				;
			break ;
		}
		if (pthread_mutex_lock(((pthread_mutex_t *)(content->fork_right))) == 0)
			ph_took_a_fork(&content, content->number);
		if (!eat_sleep_work(content, &count))
			break ;
	}
	return (NULL);
}
