/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:12:57 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/03 15:13:48 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct s_builtin {
	char *name;						// The built-in command's name (e.g., "cd", "echo")
	int (*func)(char **args);		// A pointer to the function that implements this command
} t_builtin;

extern t_builtin g_builtin[];

//int	builtin_echo(char **args);
int	builtin_cd(char **args);
int	builtin_pwd(char **args);
//int	builtin_export(char **args);
//int	builtin_unset(char **args);
int builtin_env(char **args, char **env);
//int	builtin_exit(char **args);

#endif
