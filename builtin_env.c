/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:12:23 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/03 15:12:54 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtin.h"
#include <stdio.h>

/*
 * Implémente la commande env en affichant l'environnement.
 * args : tableau d'arguments de la commande ("env" doit être seul)
 * env : tableau de chaînes représentant l'environnement (par exemple, envp de main)
 *
 * Si un argument supplémentaire est passé, on affiche une erreur.
 */
int builtin_env(char **args, char **env)
{
	int i = 0;

	// Vérifier qu'aucun argument n'est passé (env doit être exécuté sans arguments)
	if (args[1])
	{
		fprintf(stderr, "env: too many arguments\n");
		return (1);
	}
	// Afficher l'environnement
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
