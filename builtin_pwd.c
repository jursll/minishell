/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:54:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/03 13:54:23 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtin.h"

int builtin_pwd(char **args)
{
	char cwd[1024];

	// Vérifier qu'aucun argument supplémentaire n'est passé
	if (args[1])
	{
		fprintf(stderr, "pwd: too many arguments\n");
		return 1;
	}

	// Récupérer le répertoire courant
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return 1;
	}

	// Afficher le chemin absolu suivi d'un saut de ligne
	printf("%s\n", cwd);
	return 0;
}
