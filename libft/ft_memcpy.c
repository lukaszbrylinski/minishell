/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:39 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/29 03:21:36 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*pdest;
	unsigned char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *) dest;
	psrc = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (pdest);
}
// #include <stdio.h> 
// #include <string.h> 
// int main() 
// { 
//    char first[100] = "ABCDEFGHIJ"; 
//    char second[100] = "ABCDEFGHIJ";
//    printf("Original string :%s\n ", first); 
//    // when overlap happens then it just ignore it 
//    memcpy(first + 2, first, 10); 
//    printf("memcpy overlap : %s\n ", first); 
//    ft_memcpy(second + 2, second, 10); 
//    printf("ft_memcpy overlap : %s\n ", second); 
//    return 0; 
// }
