/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/03 13:39:31 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtin.h"

int builtin_cd(char **args)
{
	char	*target;
	char	*old_pwd;
	char	cwd[1024];

	// Récupérer le répertoire courant pour pouvoir mettre à jour OLDPWD plus tard
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: getcwd error");
		return (1);
	}
	old_pwd = strdup(cwd);
	if (!old_pwd)
	{
		perror("cd: strdup error");
		return (1);
	}

	// Cas sans argument ou avec "~" : utiliser la variable HOME
	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		target = getenv("HOME");
		if (!target)
		{
			fprintf(stderr, "cd: HOME not set\n");
			free(old_pwd);
			return (1);
		}
	}
	// Cas "cd -" : retourner dans OLDPWD
	else if (strcmp(args[1], "-") == 0)
	{
		target = getenv("OLDPWD");
		if (!target)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			free(old_pwd);
			return (1);
		}
		printf("%s\n", target); // Affiche le répertoire cible
	}
	else
	{
		// Optionnel : vérifier si l'argument est une chaîne vide
		if (args[1][0] == '\0')
		{
			fprintf(stderr, "cd: empty path\n");
			free(old_pwd);
			return (1);
		}
		target = args[1];
	}

	// Vérifier qu'il n'y a pas trop d'arguments
	if (args[2])
	{
		fprintf(stderr, "cd: too many arguments\n");
		free(old_pwd);
		return (1);
	}

	// Tenter de changer de répertoire
	if (chdir(target) != 0)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}

	// Mise à jour de OLDPWD
	if (setenv("OLDPWD", old_pwd, 1) != 0)
	{
		perror("cd: setenv OLDPWD");
	}
	free(old_pwd);

	// Mise à jour de PWD avec le nouveau répertoire
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: getcwd error after chdir");
		return (1);
	}
	if (setenv("PWD", cwd, 1) != 0)
	{
		perror("cd: setenv PWD");
		return (1);
	}
	return (0);
}

