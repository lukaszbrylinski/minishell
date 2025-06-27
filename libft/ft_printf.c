/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:58:40 by dszafran          #+#    #+#             */
/*   Updated: 2025/02/25 18:43:55 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_conversion(char c, va_list *args, int *i)
{
	if (c == 'c')
		*i += write_char(va_arg(*args, int));
	else if (c == 's')
		*i += write_string(va_arg(*args, char *));
	else if (c == 'p')
		*i += write_pointer((uintptr_t)va_arg(*args, void *));
	else if (c == 'i' || c == 'd')
		*i += write_number(va_arg(*args, int));
	else if (c == 'u')
		*i += write_unumber(va_arg(*args, unsigned int));
	else if (c == 'x')
		*i += write_hex("0123456789abcdef", va_arg(*args, unsigned int));
	else if (c == 'X')
		*i += write_hex("0123456789ABCDEF", va_arg(*args, unsigned int));
	else if (c == '%')
		*i += write_char('%');
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;

	va_start(args, format);
	i = 0;
	while (*format)
	{
		if (*format == '%')
			check_conversion(*(++format), &args, &i);
		else
		{
			write(1, format, 1);
			i++;
		}
		format++;
	}
	va_end(args);
	return (i);
}

// int	main()
// {
// 	char *s = "hello\nworld";
// 	// ft_printf("my string: %s", s);
// 	ft_printf("my pointer: %p", s);
// 	return (0);
// }