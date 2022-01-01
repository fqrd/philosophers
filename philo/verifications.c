/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 10:37:59 by fcaquard          #+#    #+#             */
/*   Updated: 2022/01/01 10:50:47 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_digits(char *inputs)
{
	size_t i;

	i = 0;
	while (inputs[i])
	{
		if (inputs[i] > '9' || inputs[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int verifications(int argc, char *argv[])
{
	size_t i;

	i = argc;
	while (i-- > 1)
	{
		if (!check_digits(argv[i]))
			return (0);
	}
	return (1);
}
