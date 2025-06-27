/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:42:25 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/30 18:17:02 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

//could have used memset
//#include <stdio.h>
//int main() {
//
//	char s[] = "hello";
//	ft_bzero(s, 3);
//
//    int	i = 0;
//	while (i < 5)
//	{
//		printf("%c", s[i]);
//        i++;
//    }
//    return 0;
//}