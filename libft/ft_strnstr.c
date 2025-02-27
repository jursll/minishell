/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:40:04 by julrusse          #+#    #+#             */
/*   Updated: 2024/10/23 17:27:05 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (substr[0] == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		if (str[i] == substr[0])
		{
			j = 0;
			while (str[i + j] == substr[j] && i + j < len)
			{
				if (substr[j + 1] == '\0')
					return ((char *)str + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
