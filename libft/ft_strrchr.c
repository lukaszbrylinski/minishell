/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:49:04 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/28 11:33:18 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	while (s[len] != (char) c && len > 0)
		len--;
	if (s[len] == (char) c)
		return ((char *)&s[len]);
	return (NULL);
}
//change compareson to unsigned char
// #include <stdio.h>
// int	main()
// {
// 	char s[] = "hello";
// 	printf("%c", *ft_strrchr(s, 'l'));
// 	printf("%p", ft_strrchr(s, '\0'));
// 	return (0);
// }