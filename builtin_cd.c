/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/11 16:50:54 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtin.h"

int	builtin_cd(t_command *cmd)
{
	char	cwd[MAX_PATH];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd: getcwd error");
		return (EXIT_FAILURE);
	}
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (cmd->args[1] == NULL || strcmp(cmd->args[1], "~") == 0)
		return (change_dir_home(cwd));
	else if (strcmp(cmd->args[1], "-") == 0)
		return (change_to_old_dir(cwd));
	else if (cmd->args[1][0] == '\0')
	{
		ft_putstr_fd("cd: empty path\n", 2);
		return (EXIT_FAILURE);
	}
	else
		return (execute_cd_path(cwd, cmd->args[1]));
}
