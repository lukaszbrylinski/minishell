/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:04:39 by dszafran          #+#    #+#             */
/*   Updated: 2025/02/25 18:42:36 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!s1 && !s2)
		return (NULL);
	s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	return (s[i + j] = 0, s);
}
// #include <stdio.h>
// int main()
// {
// 	char s1[] = "hi";
// 	char s2[] = "bye ";
// 	char *ptr = ft_strjoin(s1, s2);
// 	printf("%d", ft_strlen(ptr));
// 	while (*ptr != '\0')
// 	{
// 		printf("%c", *ptr);
// 		ptr++;
// 	}
// 	return (0);
// }
