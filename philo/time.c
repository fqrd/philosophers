/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:42:55 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/09 21:00:30 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_timeout(size_t duration)
{
	t_timeval	start;
	t_timeval	now;
	
	while (gettimeofday(&start, NULL) == -1) ;
	while (1)
	{
		while (gettimeofday(&now, NULL) == -1) ;
		if (now.tv_usec >= start.tv_usec + (long int)duration)
			break ;
	}
	return (1);
}

int	still_alive(size_t time_of_death)
{
	t_timeval	now;
	
	while (gettimeofday(&now, NULL) == -1) ;
	if (now.tv_usec <= (long int)time_of_death)
		return (1);
	else
		return (0);
}