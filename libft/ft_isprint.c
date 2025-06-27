/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:18:22 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/10 21:55:28 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (c);
	return (0);
}

//#include <stdio.h>
//int	main()
//{
//	printf("%d", ft_isprint('c'));
//	printf("%d", ft_isprint('0'));
//	printf("%d", ft_isprint(127));
//	return (0);
//}