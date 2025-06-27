/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:38:01 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/28 11:33:27 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != (char) c)
		i++;
	if (s[i] == (char) c)
		return ((char *)&s[i]);
	return (NULL);
}
// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	//signal(SIGSEGV, sigsegv);
// 	char s[] = "tripouille";
// 	printf("%c\n", 't' + 256);
// 	printf("%s", ft_strchr(s, 't' + 256)); //showLeaks();
// 	write(1, "\n", 1);
// 	return (0);
// }
//change compareson to unsigned char
//#include <stdio.h>
//int	main()
//{
//	char s[] = "hello";
//	printf("%c", *ft_strchr(s, 'l'));
//	printf("%p", ft_strchr(s, '\0'));
//	return (0);
//}
