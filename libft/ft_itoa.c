/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:27:25 by julrusse          #+#    #+#             */
/*   Updated: 2024/10/23 17:26:13 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static unsigned int	ft_length(int num)
{
	unsigned int	len;

	len = 0;
	if (num <= 0)
		len = 1;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	num;
	unsigned int	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_length(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	num = n;
	if (n < 0)
		num = -n;
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-123));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(1));
	printf("%s\n", ft_itoa(4567));
	return (0);
}
*/
