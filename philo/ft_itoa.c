/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:09:21 by fcaquard          #+#    #+#             */
/*   Updated: 2021/12/26 14:09:23 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*to_char(long long value, int size, char *output)
{
	if (value < 10)
	{
		output[size] = value + '0';
		return (output);
	}
	else
	{
		to_char(value / 10, size - 1, output);
		output[size] = (value % 10) + '0';
	}
	return (output);
}

static char	*below_zero(long long v, int size)
{
	char	*output;

	output = malloc(sizeof(char) * (size + 2));
	if (!output)
		return (NULL);
	output[0] = '-';
	to_char(v, size, output);
	output[size + 1] = '\0';
	return (output);
}

static char	*above_zero(long long v, int size)
{
	char	*output;

	output = malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	to_char(v, size - 1, output);
	output[size] = '\0';
	return (output);
}

char	*ft_itoa(int n)
{
	long long	v;
	int			size;
	char		*output;

	v = (long long) n;
	size = 1;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		size++;
	}
	if (v < 0)
		output = below_zero(v * (-1), size);
	else
		output = above_zero(v, size);
	if (!output)
		return (NULL);
	return (output);
}
