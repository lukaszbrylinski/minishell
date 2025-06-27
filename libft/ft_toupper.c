/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:16:54 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/04 16:28:59 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		c -= 32;
	return (c);
}

//#include <stdio.h>
//int	main()
//{
//	int	i = 0;
//	char str[] = "aBct27djriubS";
//	while (str[i])
//	{
//		printf("%c", ft_toupper(str[i]));
//		i++;
//	}
//	return (0);
//}