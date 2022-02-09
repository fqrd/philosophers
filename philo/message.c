/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:06:07 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/09 21:43:27 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

static void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

static char	*ft_concat(char *str, char *timestamp, char *philo, char *sentence)
{
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

/**
 * @brief Mallocs, concats and prints a constructed string
 * 
 * @param timestamp 
 * @param philo 
 * @param sentence 
 * @return int Success[1], Error[0]
 */
int	build_str(char *timestamp, char *philo, char *sentence)
{
	char	*message;
	size_t	i;

	i = ft_strlen(timestamp) + 1 + ft_strlen(philo) + 1
		+ ft_strlen(sentence) + 1;
	message = malloc(sizeof(char) * (i + 1));
	if (!message)
	{
		free (philo);
		free(timestamp);
		return (0);
	}
	message[i] = '\0';
	message = ft_concat(message, timestamp, philo, sentence);
	ft_putstr(message);
	free (philo);
	free(timestamp);
	free(message);
	return (1);
}
