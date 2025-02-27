/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:31:08 by julrusse          #+#    #+#             */
/*   Updated: 2024/12/22 14:52:26 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*gnl_calloc(int count, int size)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < count * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

char	*gnl_strchr(char *s, int c)
{
	unsigned char	i;

	i = (unsigned char)c;
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;
	int		s1_len;

	i = 0;
	j = 0;
	if (!s1)
		s1_len = 0;
	else
		s1_len = gnl_strlen(s1);
	str = (char *)gnl_calloc((s1_len + gnl_strlen(s2) + 1), sizeof(char));
	if (!str)
		return (free(s1), NULL);
	if (s1)
	{
		while (s1[j])
			str[i++] = s1[j++];
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	free(s1);
	return (str);
}

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_substr(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		j;

	if (!s || start >= gnl_strlen(s))
		return (NULL);
	str = (char *)gnl_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	return (str);
}
