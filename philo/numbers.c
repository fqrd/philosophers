/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:49:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/09 22:32:20 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static size_t tens(size_t n)
{
	size_t i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int size_t_to_str(size_t value, size_t size, char **output)
{
	if (value < 10)
	{
		(*output)[size] = value + '0';
		return (1);
	}
	else
	{
		size_t_to_str(value / 10, size - 1, output);
		(*output)[size] = (value % 10) + '0';
	}
	return (1);
}

char *atoi_size_t(size_t n)
{
	size_t len;
	char *str;

	len = tens(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	size_t_to_str(n, len - 1, &str);
	return (str);
}