/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:35:01 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/30 18:13:39 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (ptr);
}

//#include <stdio.h>
//int main() {
//
//	char s[] = "hello";
//	char *arr = (char *)ft_memset(s, '0', 3);
//
//    int	i = 0;
//	while (arr[i])
//	{
//		printf("%c", arr[i]);
//		i++;
//	}
//    return 0;
//}