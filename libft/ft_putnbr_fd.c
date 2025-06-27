/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:49:18 by dszafran          #+#    #+#             */
/*   Updated: 2025/03/20 09:56:02 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
		write(fd, "-", 1);
	c = ft_absolute(n % 10) + 48;
	if (n / 10 != 0)
		ft_putnbr_fd(ft_absolute(n / 10), fd);
	write(fd, &c, 1);
}
