/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:17:19 by dszafran          #+#    #+#             */
/*   Updated: 2025/02/25 18:44:03 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(unsigned int n)
{
	int	i;

	if (n == 0)
		return (1);
	else
		i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_uitoa(unsigned int n)
{
	int		j;
	char	*num;

	j = ft_count(n);
	num = (char *) malloc ((j + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[j] = '\0';
	j--;
	while (j >= 0)
	{
		num[j] = n % 10 + 48;
		n /= 10;
		j--;
	}
	return (num);
}

int	write_hex(char *hexes, unsigned int num)
{
	int		i;
	char	c;

	i = 1;
	if (num / 16 != 0)
		i += write_hex(hexes, num / 16);
	c = hexes[num % 16];
	write(1, &c, 1);
	return (i);
}

int	converter(char *hexes, uintptr_t num)
{
	int		i;
	char	c;

	i = 1;
	if (num / 16 != 0)
		i += converter(hexes, num / 16);
	c = hexes[num % 16];
	write(1, &c, 1);
	return (i);
}

int	write_pointer(uintptr_t num)
{
	if (!num)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	return (2 + converter("0123456789abcdef", num));
}
