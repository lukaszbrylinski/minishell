/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:42:28 by dszafran          #+#    #+#             */
/*   Updated: 2025/03/20 09:55:43 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	i;

	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i = 1;
	}
	else
		i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		j;
	int		i;
	char	*num;

	j = ft_count(n);
	i = 0;
	num = (char *) malloc ((j + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[j] = '\0';
	j--;
	if (n < 0)
	{
		num[0] = '-';
		i = 1;
	}
	while (j >= i)
	{
		num[j] = ft_absolute(n % 10) + 48;
		ft_absolute(n /= 10);
		j--;
	}
	return (num);
}
// #include <stdio.h>
// int	main()
// {
// 	printf("%s", ft_itoa(-2147483647 -1));
// 	return (0);
// }