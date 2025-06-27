/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:25:13 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/30 19:11:17 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen((char *)src);
	i = 0;
	if (size == 0)
		return (len);
	while ((i < size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

// what if dest_s is bigger tham src?
// #include <stdio.h>
// #include <string.h>
// int	main()
// {
// 	char *dest = NULL;
// 	char src[] = "hello111111";
// 	size_t src_len = ft_strlcpy(dest, src, sizeof(dest));
// 	printf("dest: %s, size of dest: %lu\n", dest, sizeof(dest));
// 	printf("result: %s\n", dest);
// 	printf("return (src len): %lu\n", src_len);
// 	return (0);
// }