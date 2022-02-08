/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:42:55 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/08 16:42:11 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_timeout(size_t timeout)
{
	t_timeval	tv;

	while (1)
	{
		while (gettimeofday(&tv, NULL) > -1)
		{
			if (tv.tv_usec >= (long int)timeout)
			{
				// printf("timeout: %ld\n", timeout);
				return (1);
			}
		}
	}
	return (0);
}

int	still_alive(size_t time_of_death)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL) <= -1)
		return (0);
	if (tv.tv_usec >= (long int)time_of_death)
		return (0);
	else
		return (1);
}