/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:49:45 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/28 15:12:10 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	str_len;

	if (!s)
		return (NULL);
	if ((size_t) start >= ft_strlen(s))
		return (ft_strdup(""));
	str_len = ft_strlen(s) - start;
	if (str_len > len)
		str_len = len;
	sub = (char *) malloc(str_len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (s[i + (size_t) start] && i < len)
	{
		sub[i] = s[i + (size_t) start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
// #include <string.h>
// int	main()
// {
// 	char s[] = "01234";
// 	char *result = ft_substr(s, 10, 10);
// 	if (!strncmp(result, "", 1))
// 	{
// 		free(result);
// 		printf("gg");
// 	}
// 	else 
// 		free(result);
// 	return (0);
// }