/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:12:57 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/11 17:06:41 by julrusse         ###   ########.fr       */
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
#include <ctype.h>

typedef struct s_builtin {
	char *name;						// The built-in command's name (e.g., "cd", "echo")
	int (*func)(char **args);		// A pointer to the function that implements this command
} t_builtin;

// dans minishell.h
typedef struct s_command {
    char    *cmd;             // Command name (e.g., "echo")
    int     suppress_newline; // 1 if -n is provided, else 0
    char    **args;           // Array of argument strings
    int     arg_count;        // Number of arguments
	// New fields for redirections:
	char    *input_file;      // For '<'
	char    *output_file;     // For '>' or '>>'
	int     append_mode;      // 0 for '>', 1 for '>>'
	char    *heredoc_delimiter; // For '<<'
	int		has_heredoc;
	int		expand_heredoc;
	struct s_command *next;   // Next command in a pipeline
} t_command;

extern t_builtin g_builtin[];



//int	builtin_echo(char **args);

int		builtin_cd(t_command *cmd);
int		change_dir_home(char *cur_pwd);
int		change_to_old_dir(char *cur_pwd);
int		execute_cd_path(char *cur_pwd, char *path);
int		update_directories(const char *old_pwd);

int		builtin_env(t_command *cmd, char **env);

int		builtin_pwd(t_command *cmd);

int		builtin_export(t_command *cmd, char ***env);
int		env_op(char **env, const char *key, int mode);
int		set_env_var(char ***env_ptr, const char *assignment);
int		is_valid_identifier_export(const char *token);
int		cmpfunc(const void *a, const void *b);
void	print_sorted_env(char **env);

int		builtin_unset(t_command *cmd, char ***env);
int		valid_unset_identifier(const char *token);
int		env_remove_var(char ***env_ptr, const char *key);
int		env_idx(char **env, const char *key);
int		env_len(char **env);


//int	builtin_exit(char **args);

#endif
