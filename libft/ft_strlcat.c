/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:08:19 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/30 19:34:28 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_src = (size_t) ft_strlen(src);
	if (!size)
		return (len_src);
	len_dst = (size_t) ft_strlen(dst);
	if (len_dst >= size)
		return (size + len_src);
	i = 0;
	while (src[i] && (i < size - len_dst - 1))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
//could be also check for 
// #include <stdio.h>
// #include <string.h>
//  int main()
// {
// 	size_t size = -1;
// 	char dest[30]; memset(dest, 0, 30);
// 	char * src = (char *)"AAAAAAAAA";
// 	memset(dest, 'C', 5);
// 	printf("%lu\n", size);
// 	printf("%lu\n", ft_strlcat(dest, src, size));
// 	printf("%s", dest);
// 	return (0);
// }
// int	main()
// {
// 	char dest[8] = "hello ";
// 	char src[] = "world";
// 	printf("len of target str: %zu\n", ft_strlcat(dest, src, sizeof(dest)));
// 	printf("string in dest: %s", dest);
// 	return (0);
// }
// int main()
// {
// 	char *str = "the cake is a lie !\0I'm hidden lol\r\n";
// 	char buff1[0xF00] = "there is no stars in the sky";
// 	char buff2[0xF00] = "there is no stars in the sky";
// 	size_t max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;

// 	strlcat(buff1, str, max);
// 	ft_strlcat(buff2, str, max);
// 	if (!strcmp(buff1, buff2))
// 		printf("TEST_SUCCESS");
// 	else
// 		printf("TEST_FAILED");
// 	return (0);
// }
