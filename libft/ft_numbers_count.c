/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:19:10 by julrusse          #+#    #+#             */
/*   Updated: 2024/10/25 12:24:31 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr_count(int number)
{
	int	count;

	count = 0;
	if (number == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (number < 0)
	{
		count += ft_putchar_count('-');
		number *= -1;
	}
	if (number > 9)
		count += ft_putnbr_count(number / 10);
	count += ft_putchar_count(number % 10 + '0');
	return (count);
}

int	ft_unsignedint_count(unsigned int number)
{
	int	count;

	count = 0;
	if (number >= 10)
		count += ft_unsignedint_count(number / 10);
	count += ft_putchar_count(number % 10 + '0');
	return (count);
}

int	ft_hex_count(unsigned int number, int uppercase)
{
	int	count;
	int	hexnumber;

	count = 0;
	if (number >= 16)
		count += ft_hex_count(number / 16, uppercase);
	hexnumber = number % 16;
	if (hexnumber < 10)
		count += ft_putchar_count(hexnumber + '0');
	else
	{
		if (uppercase)
			count += ft_putchar_count(hexnumber - 10 + 'A');
		else
			count += ft_putchar_count(hexnumber - 10 + 'a');
	}
	return (count);
}

static int	ft_hexptr_count(unsigned long int number)
{
	int	count;
	int	hexnumber;

	count = 0;
	if (number >= 16)
		count += ft_hexptr_count(number / 16);
	hexnumber = number % 16;
	if (hexnumber < 10)
		count += ft_putchar_count(hexnumber + '0');
	else
		count += ft_putchar_count(hexnumber - 10 + 'a');
	return (count);
}

int	ft_ptr_count(void *ptr)
{
	int				count;
	unsigned long	address;

	count = 0;
	address = (unsigned long)ptr;
	count += ft_putchar_count('0');
	count += ft_putchar_count('x');
	if (!ptr)
		count += ft_putchar_count('0');
	else
		count += ft_hexptr_count(address);
	return (count);
}
