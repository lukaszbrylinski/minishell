/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:23:16 by dszafran          #+#    #+#             */
/*   Updated: 2025/02/27 17:21:56 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sum;
	int	minus;

	sum = 0;
	minus = 1;
	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus *= -1;
		i++;
	}
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			break ;
		sum *= 10;
		sum += (nptr[i] - '0');
		i++;
	}
	return (sum * minus);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char nptr[] = "\t\v\f\r\n \f- \f\t\n\r    06050";
// 	printf("%d",ft_atoi(nptr));
// 	return (0);
// }