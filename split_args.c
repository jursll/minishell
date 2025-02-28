/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/27 19:04:57 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <ctype.h> // Pour isspace()

t_token	*tokenize_input(char *input)
{
	t_token	*token_list = NULL;
	char	*word;
	int		i = 0, j;
	char	quote_char = 0;

	while (input[i])
	{
		while (isspace(input[i])) // Ignorer les espaces
			i++;
		if (!input[i])
			break;
		j = i;
		if (input[i] == '"' || input[i] == '\'') // Détection d'un début de guillemets
		{
			quote_char = input[i]; // Définir quel type de guillemet est utilisé
			j++; // Passer le premier guillemet
			while (input[j] && input[j] != quote_char) // Aller jusqu'au guillemet fermant
				j++;
			if (input[j] == quote_char) // Si on trouve le guillemet fermant, l'inclure
				j++;
		}
		else if (strchr("|<>$", input[i])) // Si c'est un opérateur
		{
			if ((input[i] == '>' && input[i + 1] == '>') ||
				(input[i] == '<' && input[i + 1] == '<')) // Gestion de `>>` et `<<`
				j++;
			j++;
		}
		else // Si c'est un mot (commande/argument normal)
		{
			while (input[j] && !isspace(input[j]) && !strchr("|<>$", input[j]))
				j++;
		}
		word = strndup(&input[i], j - i); // Extraire le token
		add_token(&token_list, create_token(word, get_token_type(word)));
		free(word);
		i = j;
	}
	return (token_list);
}

static int	count_args(char *input)
{
	int	count = 0;
	int	in_quotes = 0;

	while (*input)
	{
		while (*input == ' ')
			input++;
		if (*input)
			count++;
		while (*input && (*input != ' ' || in_quotes))
		{
			if (*input == '"' || *input == '\'')
				in_quotes = !in_quotes;
			input++;
		}
	}
	return (count);
}

static char	*extract_arg(char **input)
{
	char	*start = *input;
	char	*arg;
	int		in_quotes = 0;

	while (**input && (**input != ' ' || in_quotes))
	{
		if (**input == '"' || **input == '\'')
			in_quotes = !in_quotes;
		(*input)++;
	}
	arg = strndup(start, *input - start);
	if (**input)
		(*input)++;
	return (arg);
}

char	**split_arguments(char *input)
{
	int		arg_count;
	char	**argv;
	int		i = 0;

	arg_count = count_args(input);
	argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!argv)
		return (NULL);
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (*input)
			argv[i++] = extract_arg(&input);
	}
	argv[i] = NULL;
	return (argv);
}
