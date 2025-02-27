/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:22:00 by julrusse          #+#    #+#             */
/*   Updated: 2024/10/23 17:26:40 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_countstr(char const *s, char c)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, n + 1);
	return (str);
}

static char	**ft_free_tab(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

static int	ft_add_words(char **tab, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			tab[k] = ft_strndup(s + j, i - j);
			if (!tab[k])
				return (0);
			k++;
		}
	}
	tab[k] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;
	int		addwords;

	if (!s)
		return (NULL);
	count = ft_countstr(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	addwords = ft_add_words(tab, s, c);
	if (!addwords)
		return (ft_free_tab(tab, count));
	return (tab);
}
/*
int	main(void)
{
	char a[] = "   WTF  cette   fonction de m  ";
	char b = ' ';
	char **result;
	int i;

	result = ft_split(a, b);
	i = 0;
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/
/*
int	main(void)
{
	char a[] = "hello!";
	char b = ' ';
	char **result;
	int i;

	result = ft_split(a, b);
	i = 0;
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/
