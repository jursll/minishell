/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:35:54 by julrusse          #+#    #+#             */
/*   Updated: 2024/10/23 17:25:53 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t len)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
}
