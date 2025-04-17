/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:43:02 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/11 16:38:41 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtin.h"

/*
** set_env_var:
**   Adds or updates a variable in the environment.
**   'assignment' is of the form "KEY=VALUE" or "KEY". In the latter case,
**   the variable is added with an empty value.
*/
int	set_env_var(char ***env_ptr, const char *assignment)
{
	char	**env;
	char	*eq;
	char	key[256];
	int		key_len;
	int		idx;

	env = *env_ptr;
	eq = strchr(assignment, '=');
	if (eq)
		key_len = eq - assignment;
	else
		key_len = strlen(assignment);
	if (key_len >= (int)sizeof(key))
		key_len = sizeof(key) - 1;
	strncpy(key, assignment, key_len);
	key[key_len] = '\0';
	idx = env_op(env, key, 1);
	if (!eq)
	{
		if (idx == -1)
		{
			int		count;

			count = env_op(env, NULL, 0);
			env = realloc(env, (count + 2) * sizeof(char *));
			if (!env)
				return (1);
			env[count] = malloc(key_len + 2);
			if (!env[count])
				return (1);
			strcpy(env[count], key);
			strcat(env[count], "=");
			env[count + 1] = NULL;
			*env_ptr = env;
		}
	}
	else
	{
		char	*new_entry;
		int		count;

		new_entry = strdup(assignment);
		if (!new_entry)
			return (1);
		if (idx != -1)
		{
			free(env[idx]);
			env[idx] = new_entry;
		}
		else
		{
			count = env_op(env, NULL, 0);
			env = realloc(env, (count + 2) * sizeof(char *));
			if (!env)
			{
				free(new_entry);
				return (1);
			}
			env[count] = new_entry;
			env[count + 1] = NULL;
			*env_ptr = env;
		}
	}
	return (0);
}

int	builtin_export(t_command *cmd, char ***env)
{
	int	ret;
	int	i;

	ret = 0;
	i = 1;
	if (!cmd->args[i])
	{
		print_sorted_env(*env);
		return (0);
	}
	while (cmd->args[i])
	{
		if (!is_valid_identifier_export(cmd->args[i]))
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n",
				cmd->args[i]);
			ret = 1;
		}
		else
		{
			if (set_env_var(env, cmd->args[i]) != 0)
				ret = 1;
		}
		i++;
	}
	return (ret);
}

