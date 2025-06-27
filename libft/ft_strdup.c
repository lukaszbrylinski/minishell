/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:49:21 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/26 19:00:33 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	if (!s)
		return (NULL);
	ptr = (char *) malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr[i] = 0, ptr);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char *source = "";

//     // A copy of source is created dynamically
//     // and pointer to copy is returned.
//     char* target = ft_strdup(source); 
// 	if (strcmp(source, target))
// 		printf("fail :(");
// 	else
// 		printf("should be ok");
//     return 0;
// }
