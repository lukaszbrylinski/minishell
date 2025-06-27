/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:39:49 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/02 15:21:30 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c > -1 && c < 128)
		return (1);
	return (0);
}

//#include <stdio.h>
//int main(void)
//{
//    printf("%d", ft_isascii('z'));
//    return (0);
//}