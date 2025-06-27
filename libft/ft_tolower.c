/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:28:48 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/04 16:36:28 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		c += 32;
	return (c);
}

// #include <stdio.h>
// int	main()
// {
// 	int	i = 0;
// 	char str[] = "aBct27djriubS";
// 	while (str[i])
// 	{
// 		printf("%c", ft_tolower(str[i]));
// 		i++;
// 	}
// 	return (0);
// }