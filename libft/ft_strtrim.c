/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:48:53 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/26 19:43:00 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	if (!set || !s1)
		return (NULL);
	i = -1;
	while (s1[++i])
		if (ft_strrchr(set, s1[i]) == NULL)
			break ;
	j = ft_strlen((char *)s1);
	while (--j > i)
		if (ft_strrchr(set, s1[j]) == NULL)
			break ;
	ptr = (char *) malloc(j - i + 2);
	if (!ptr)
		return (NULL);
	k = -1;
	while (++k + i <= j)
		ptr[k] = s1[i + k];
	ptr[k] = '\0';
	return (ptr);
}
// #include <stdio.h>
// int	main()
// {
// 	char s1[] = "xyzyxyzyxyyabcdefghicxzyxyzydxyzyz";
// 	char set[] = "xyz";
// 	printf("%s", ft_strtrim(s1, set));
// 	return (0);
// }