/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_writing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:11:03 by dszafran          #+#    #+#             */
/*   Updated: 2025/02/25 18:44:18 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_string(char *s)
{
	int		i;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	write_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	write_number(int n)
{
	char	*arr;
	int		i;

	arr = ft_itoa(n);
	i = ft_strlen(arr);
	write(1, arr, i);
	return (free(arr), i);
}

int	write_unumber(unsigned int n)
{
	char	*arr;
	int		i;

	arr = ft_uitoa(n);
	i = ft_strlen(arr);
	write(1, arr, i);
	return (free(arr), i);
}
