/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:46:36 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/27 18:53:14 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %-10s | Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

void	print_arguments(char **args)
{
	int i = 0;
	while (args[i])
	{
		printf("Arg[%d]: %s\n", i, args[i]);
		i++;
	}
}

int	main(void)
{
	char		*input;
	t_token		*tokens;
	char		**args;

	// Simulation d'une entrée utilisateur
	input = "echo \"hello world\" | cat -e > file.txt";

	// Étape 1 : Tokenization
	printf("\n🔹 Tokenization:\n");
	tokens = tokenize_input(input);  // À modifier si besoin
	print_tokens(tokens);

	// Étape 2 : Split en arguments
	printf("\n🔹 Arguments split:\n");
	args = split_arguments(input);
	print_arguments(args);

	// Libération mémoire
	free_tokens(&tokens);
	for (int i = 0; args[i]; i++)
		free(args[i]);
	free(args);

	return (0);
}
