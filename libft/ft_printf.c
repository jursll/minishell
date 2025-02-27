/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:57:30 by julrusse          #+#    #+#             */
/*   Updated: 2024/10/25 12:06:41 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_select_arg(char c, va_list *args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar_count((char)va_arg(*args, int));
	else if (c == 's')
		count = ft_putstr_count(va_arg(*args, char *));
	else if (c == 'p')
		count += ft_ptr_count(va_arg(*args, void *));
	else if (c == 'd' || c == 'i')
		count = ft_putnbr_count(va_arg(*args, int));
	else if (c == 'u')
		count = ft_unsignedint_count(va_arg(*args, unsigned int));
	else if (c == 'X')
		count += ft_hex_count(va_arg(*args, unsigned int), 1);
	else if (c == 'x')
		count += ft_hex_count(va_arg(*args, unsigned int), 0);
	else if (c == '%')
		count = ft_putchar_count('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		result;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			result = ft_select_arg(format[i], &args);
			count += result;
		}
		else
			count += ft_putchar_count(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
