/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:42:42 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/29 03:17:10 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	if (src > dest)
	{
		i = -1;
		while (++i < n)
			pdest[i] = psrc[i];
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			pdest[i] = psrc[i];
		}
	}
	return (pdest);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char first[100] = "ABCDEFGHIJ";
//     char second[100] = "ABCDEFGHIJ";

//     printf("Original string :%s\n ", first);

//     memmove(first + 2, first, 10);
//     printf("memmove overlap : %s\n ", first);

//     // when overlap it start from first position
//     ft_memmove(second + 2, second, 10);
//     printf("ft_memmove overlap : %s\n ", second);

//     return 0;
// }