/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:44:14 by julrusse          #+#    #+#             */
/*   Updated: 2025/02/27 18:09:18 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

t_token_type	get_token_type(char *str)
{
	if (!ft_strncmp(str, "|", SIZE_MAX))
		return (PIPE);
	if (!ft_strncmp(str, "<", SIZE_MAX))
		return (REDIR_IN);
	if (!ft_strncmp(str, ">", SIZE_MAX))
		return (REDIR_OUT);
	if (!ft_strncmp(str, ">>", SIZE_MAX))
		return (APPEND);
	if (!ft_strncmp(str, "<<", SIZE_MAX))
		return (HEREDOC);
	if (!ft_strncmp(str, "$", SIZE_MAX))
		return (DOLLAR);
	if (!ft_strncmp(str, "$?", SIZE_MAX))
		return (EXIT_STATUS);
	return (WORD);
}

void	categorize_tokens(t_token *tokens)
{
	while (tokens)
	{
		tokens->type = get_token_type(tokens->value);
		tokens = tokens->next;
	}
}

void	free_tokens(t_token **head)
{
	t_token	*temp;
	t_token	*next;

	if (!head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		next = temp->next;
		free(temp->value);
		free(temp);
		temp = next;
	}
	*head = NULL;
}
