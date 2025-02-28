/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:12:57 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/27 19:00:49 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef	enum	e_token_type
{
	WORD,			// Commande ou argument
	PIPE,			// |
	REDIR_IN,		// <
	REDIR_OUT,		// >
	APPEND,			// >>
	HEREDOC,		// <<
	DOLLAR,			// $ suivi d'un mot (expansion de variables)
	EXIT_STATUS,	// $? (expansion du statut de sortie)
	END				// Fin de l'analyse lexicale
}				t_token_type;

typedef	struct	s_token
{
	char			*value;	// Contenu du token ("echo", "ls", ">", "|", etc.)
	t_token_type	type;	// Type de token (commande, pipe, redirection…)
	struct s_token	*next;	// Token suivant (liste chaînée)
} t_token;

t_token			*create_token(char *value, t_token_type type);
void			add_token(t_token **head, t_token *new_token);
t_token_type	get_token_type(char *str);
void			categorize_tokens(t_token *tokens);
void			free_tokens(t_token **head);


char			**split_arguments(char *input);
t_token			*tokenize_input(char *input);;

#endif
