/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:39:41 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/19 19:18:34 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	is_complete(t_ph *c)
{
	if (pthread_mutex_lock(&c->args->completed_mutex) == 0)
	{
		if (++c->args->threads_completed >= c->args->number)
		{
			if (pthread_mutex_lock(&c->args->simulation_mutex) == 0)
			{
				if (c->args->simulation_off == 0)
					c->args->simulation_off = 1;
				c->thread_active = 0;
				pthread_mutex_unlock(&c->args->completed_mutex);
				pthread_mutex_unlock(&c->args->simulation_mutex);
				return (1);
			}
		}
		pthread_mutex_unlock(&c->args->completed_mutex);
	}
	return (0);
}

static int	eat_sleep_work(t_ph *c, size_t *count)
{
	int	res;

	res = ph_eat(&c, c->number, c->args->feed_time);
	pthread_mutex_unlock(&c->fork_left);
	pthread_mutex_unlock(c->fork_right);
	if (!res)
		return (0);
	if (c->args->feed_max != 0
		&& ++(*count) >= c->args->feed_max
		&& c->thread_active == 1)
	{
		if (is_complete(c))
			return (0);
	}
	if (!ph_sleep(&c, c->number, c->args->sleep_time))
		return (0);
	if (!ph_think(&c, c->number))
		return (0);
	return (1);
}

void	*runtime(void *list)
{
	size_t	count;
	t_ph	*c;

	count = 0;
	c = ((t_ph *)(((t_list *)(list))->content));
	while (c->thread_active == 0)
		;
	if (c->number % 2 == 0)
		ft_pause(&c, 50);
	while (c->thread_active == 1)
	{
		if (pthread_mutex_lock(&(c->fork_left)) == 0)
			ph_took_a_fork(&c, c->number);
		if (c->fork_right == NULL)
		{
			pthread_mutex_unlock(&c->fork_left);
			break ;
		}
		if (pthread_mutex_lock(c->fork_right) == 0)
			ph_took_a_fork(&c, c->number);
		if (!eat_sleep_work(c, &count))
			break ;
	}
	return (NULL);
}
