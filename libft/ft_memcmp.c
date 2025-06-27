/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:13:35 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/29 03:21:00 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*chr_s1;
	unsigned char	*chr_s2;

	if (n == 0)
		return (0);
	chr_s1 = (unsigned char *)s1;
	chr_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (chr_s1[i] != chr_s2[i])
			return (chr_s1[i] - chr_s2[i]);
		i++;
	}
	return (0);
}
// int	main()
// {
// 	char s1[] = {0, 0, 0, 127};
// 	char s2[] = {0, 0, 0, 42};
// 	printf("%d", ft_memcmp(s1, s2, 4));
// 	return (0);
// }