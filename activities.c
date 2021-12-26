/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:01:29 by fcaquard          #+#    #+#             */
/*   Updated: 2021/12/26 14:48:28 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_nbrlen(long long n)
{
	size_t	i;

	i = 1;
	while (n > 10 || n <= -10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

size_t ft_strlen(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

char *ft_concat(char *str, char *timestamp, char *philo, char *sentence)
{
	(void)timestamp;
	(void)philo;
	(void)sentence;
	size_t	i;

	i = 0;

	while (*timestamp)
	{
		str[i] = *timestamp;
		timestamp++;
		i++;
	}
	str[i++] = ' ';
	while (*philo)
	{
		str[i] = *philo;
		philo++;
		i++;
	}
	str[i++] = ' ';
	while (*sentence)
	{
		str[i] = *sentence;
		sentence++;
		i++;
	}
	str[i++] = '\n';
	return (str);
}

char *build_str(char *timestamp, char *philo, char *sentence)
{
	char *str;
	size_t	i;

	i = ft_strlen(timestamp) + 1 + ft_strlen(philo) + 1 + ft_strlen(sentence) + 1;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	str = ft_concat(str, timestamp, philo, sentence);
	free (philo);		// free itoa
	free(timestamp);	// free itoa
	return (str);
}

int	took_a_fork(size_t philo)
{
	char		*message;
	char		*sentence;
	t_timeval	tv;

	message = NULL;
	sentence = "has taken a fork";

	if (gettimeofday(&tv, NULL) > -1)
	{
		message = build_str(ft_itoa(tv.tv_sec), ft_itoa(philo), sentence);
		if (!message)
			return (0);
		ft_putstr(message);
		free(message);	// free build_str
	}
	else
		return (0);
	return (1);
}

void	*ph_eat(void)
{
	// char *sentence;

	// sentence = "is eating";
	return (NULL);
}

void	*ph_sleep(void)
{
	// char *sentence;

	// sentence = "is sleeping";
	return (NULL);
}

void	*ph_think(void)
{
	// char *sentence;

	// sentence = "is thinking";
	return (NULL);
}

void	*ph_died(void)
{
	// char *sentence;

	// sentence = "died";
	return (NULL);
}
