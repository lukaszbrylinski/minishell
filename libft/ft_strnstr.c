/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:46:39 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/28 14:55:22 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	if (!len)
		return (NULL);
	i = 0;
	j = 0;
	while (big[i] && (i < len))
	{
		j = 0;
		while (big[i + j] == little[j] && j + i < len)
		{
			if (!little[j + 1])
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// int main()
// {
// 	char haystack[30] = "aaabcabcd";
// 	//char needle[10] = "aabc";
// 	//char * empty = (char*)"";
// 	printf("%d", ft_strnstr(haystack, "a", 1)==haystack);
// 	return (0);
// }
// int	main()
// {
// 	char big[]= "oh no not the empty string !";
// 	char small[] = "";
// 	char* p;

//     p = ft_strnstr(big, small, 9);
// 	if (p)
// 	{
//         printf("String found\n");
//         printf("First occurrence of string '%s' in '%s' is "
//                "'%s'",
//                big, small, p);
//     }
// 	return (0);
// }